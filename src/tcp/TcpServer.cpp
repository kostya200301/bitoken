//
// Created by Константин Беляков on 22.08.2024.
//

#include "TcpServer.h"
#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>
#include <spdlog/spdlog.h>

namespace tcp {

    TcpServer::TcpServer(boost::asio::io_context& io_context, short port)
            : io_context_(io_context),
              acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

    void TcpServer::start_accept() {
        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        acceptor_.async_accept(*socket,
                               [this, socket](const boost::system::error_code& error) {
                                   handle_accept(socket, error);
                               });
    }

    void TcpServer::handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                                  const boost::system::error_code& error) {
        if (!error) {
            auto client_id = get_client_id(socket);
            {
                std::lock_guard<std::mutex> lock(mtx_);
                active_connections_[client_id] = socket;
            }
            add_stream_buf(client_id);


            spdlog::info("[TCP] TcpServer: add user: {}", client_id);

            read_from_client(socket); // Start reading from client
        } else {
            spdlog::error("[TCP] TcpServer: Accept failed: {}", error.message());
        }
        start_accept();
    }

    void TcpServer::read_from_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        std::string client_id = get_client_id(socket);
        auto buffer = get_stream_buf(client_id);

        if (buffer == nullptr) {
            spdlog::error("[TCP] TcpServer: Get stream buffer failed, client_id: {}", client_id);
        }

        socket->async_read_some(buffer->prepare(1024),
                                [this, socket, buffer, client_id](const boost::system::error_code& error, std::size_t bytes_transferred) {
                                    if (!error) {
                                        buffer->commit(bytes_transferred);
                                        spdlog::info("[TCP] TcpServer: Receive message from {}", client_id);
                                        new_message(client_id);
                                        read_from_client(socket);
                                    } else {
                                        {
                                            std::lock_guard<std::mutex> lock(mtx_);
                                            active_connections_.erase(client_id);
                                        }
                                        spdlog::info("[TCP] TcpServer: TcpServer: del user: {}", client_id);
                                        del_stream_buf(client_id);
                                    }
                                });
    }

    void TcpServer::send_to_client(const std::string& client_id, const std::string& message) {
        auto it = active_connections_.find(client_id);
        if (it != active_connections_.end()) {
            auto socket = it->second;
            auto msg = std::make_shared<std::string>(message + "\n");
            boost::asio::async_write(*socket, boost::asio::buffer(*msg),
                                     [msg](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
                                         if (error) {
                                             spdlog::error("[TCP] TcpServer: Send failed: {}", error.message());
                                         }
                                     });
        } else {
            spdlog::error("[TCP] TcpServer: Client not found: {}", client_id);
        }
    }

    void TcpServer::add_stream_buf(const std::string& con_id) {
        spdlog::info("[TCP] TcpServer: add stream buf: {}", con_id);
        std::lock_guard<std::mutex> lock(mtx_buffers_);
        buffers_[con_id] = std::make_shared<boost::asio::streambuf>();
    }

    void TcpServer::del_stream_buf(const std::string& con_id) {
        spdlog::info("[TCP] TcpServer: del stream buf: {}", con_id);
        std::lock_guard<std::mutex> lock(mtx_buffers_);
        buffers_.erase(con_id);
    }

    std::shared_ptr<boost::asio::streambuf> TcpServer::get_stream_buf(const std::string& con_id) {
        std::lock_guard<std::mutex> lock(mtx_buffers_);
        auto it = buffers_.find(con_id);
        if (it != buffers_.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    ReadJSONStatus TcpServer::read_one_json(const std::string& con_id) {
        spdlog::trace("[TCP] TcpServer: start read JSON from buf for: {}", con_id);

        auto buf = buffers_[con_id]->data();
        auto begin = boost::asio::buffers_begin(buf);
        auto end = boost::asio::buffers_end(buf);
        auto begin_json = boost::asio::buffers_begin(buf);

        bool found_json_start = false;

        for (auto it = begin; it != end; ++it) {
            if (*it == 'I' and ((it + 1) != end and *(it + 1) == '{')) {
                begin_json = it;
                found_json_start = true;
            } else if (*it == '}' and ((it + 1) != end and *(it + 1) == 'I')) {
                if (found_json_start) {
                    std::string result(begin_json + 1, it + 1);
                    spdlog::info("[TCP] TcpServer: get JSON from con_id: {}", con_id);
                    spdlog::trace("[TCP] TcpServer: revived mes: {}", result);
                    on_new_message_(con_id, result);
                    {
                        std::lock_guard<std::mutex> lock(mtx_);
                        buffers_[con_id]->consume(begin_json - begin + 1);
                        buffers_[con_id]->consume(it - begin_json + 1);
                    }
                    if (end - begin == (begin_json - begin) + (it - begin_json) + 2) {
                        return ReadJSONStatus::FoundAll;
                    }
                    return ReadJSONStatus::FoundPart;
                }
            }
        }
        if (!found_json_start) {
            std::lock_guard<std::mutex> lock(mtx_);
            buffers_[con_id]->consume(end - begin + 1);
        } else {
            buffers_[con_id]->consume(begin_json - begin);
        }
        spdlog::warn("[TCP] TcpServer: buffer empty or without JSON");
        return ReadJSONStatus::NothingFound;
    }

    void TcpServer::new_message(const std::string& con_id) {
        handle_message(con_id);
    }

    void TcpServer::handle_message(const std::string& con_id) {
        while (read_one_json(con_id) == ReadJSONStatus::FoundPart) {

        }
    }

    int TcpServer::get_stream_buf_length(const std::string& con_id) {
        return get_stream_buf(con_id)->size();
    }

    std::string TcpServer::get_client_id(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        return socket->remote_endpoint().address().to_string() + ":" +
               std::to_string(socket->remote_endpoint().port());
    }

    TcpServer::~TcpServer() {
        boost::system::error_code ec;
        auto p = acceptor_.close(ec);
        if (ec) {
            spdlog::error("[TCP] TcpServer: Error closing acceptor: {}", ec.message());
        }
    }


}

