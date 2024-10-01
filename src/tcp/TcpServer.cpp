//
// Created by Константин Беляков on 22.08.2024.
//

#include "TcpServer.h"
#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>
#include <spdlog/spdlog.h>

// YBRAT
#include "tcp/Buffer.h"

namespace tcp {

    TcpServer::TcpServer(boost::asio::io_context& io_context, short port, const BuffersManagerPtr& buffers_manager)
            : io_context_(io_context),
              acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        buffers_manager_ = buffers_manager;
    }

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
            buffers_manager_->add_new_client(client_id);

            spdlog::info("[TCP] TcpServer: add user: {}", client_id);

            read_from_client(socket); // Start reading from client
        } else {
            spdlog::error("[TCP] TcpServer: Accept failed: {}", error.message());
        }
        start_accept();
    }

    void TcpServer::read_from_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        std::string client_id = get_client_id(socket);

        auto buffer = buffers_manager_->get_buffer();

        if (buffer == nullptr) {
            spdlog::error("[TCP] TcpServer: Get stream buffer failed, client_id: {}", client_id);
        }

        socket->async_read_some(buffer->get_boost_buffer()->prepare(5000),
                                [this, socket, buffer, client_id](const boost::system::error_code& error,
                                                std::size_t bytes_transferred) {
                                    if (!error) {
                                        buffer->get_boost_buffer()->commit(bytes_transferred);
                                        spdlog::info("[TCP] TcpServer: Receive message from {}", client_id);
                                        buffers_manager_->add_new_buffer(client_id, buffer);
                                        read_from_client(socket);
                                    } else {
                                        {
                                            std::lock_guard<std::mutex> lock(mtx_);
                                            active_connections_.erase(client_id);
                                        }
                                        spdlog::info("[TCP] TcpServer: TcpServer: del user: {}", client_id);
                                        buffers_manager_->del_client(client_id);
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

    std::string TcpServer::get_client_id(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        return socket->remote_endpoint().address().to_string() + ":" +
               std::to_string(socket->remote_endpoint().port());
    }

    TcpServer::~TcpServer() {
        spdlog::info("[TCP] TcpServer: start destroying");
        boost::system::error_code ec;
        auto p = acceptor_.close(ec);
        if (ec) {
            spdlog::error("[TCP] TcpServer: Error closing acceptor: {}", ec.message());
        }
        spdlog::info("[TCP] TcpServer: destroyed");
    }


}

