//
// Created by Константин Беляков on 23.08.2024.
//

#include "TcpClient.h"
#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>
#include <spdlog/spdlog.h>

namespace tcp {

    TcpClient::TcpClient(boost::asio::io_context& io_context,
                         const std::string& server,
                         short port)
            : io_context_(io_context),
              socket_(io_context),
              server_(server),
              port_(port) {
    }

    void TcpClient::start() {
        boost::asio::ip::tcp::resolver resolver(io_context_);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(server_, std::to_string(port_));

        boost::asio::async_connect(socket_, endpoints,
                                   [this](const boost::system::error_code& error, const boost::asio::ip::tcp::endpoint&) {
                                       handle_connect(error);
                                   });
    }

    void TcpClient::handle_connect(const boost::system::error_code& error) {
        if (!error) {
            spdlog::info("[TCP] TcpClient: Connect succeeded");
            start_reading();
        } else {
            spdlog::error("[TCP] TcpClient: Connect failed {}", error.message());
        }
    }

    void TcpClient::send_message(const std::string& message) {
        bool do_write_ = false;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            message_queue_.push(message);
            if (!wright_in_process) {
                wright_in_process = true;
                do_write_ = true;
            }
        }
        if (do_write_) {
            do_write();
        }
    }

    void TcpClient::do_write() {
        auto buffer = std::make_shared<std::string>(message_queue_.front());
        boost::asio::async_write(socket_, boost::asio::buffer(*buffer),
                                 [this, buffer](const boost::system::error_code& error, std::size_t) {
                                     if (!error) {
                                         spdlog::info("[TCP] TcpClient: Sent message to {}", get_server_id());
                                         spdlog::trace("[TCP] TcpClient: Sent message {}", *buffer);
                                         bool queue_empty = true;
                                         {
                                             std::lock_guard<std::mutex> lock(m_mutex);
                                             message_queue_.pop();
                                             queue_empty = message_queue_.empty();
                                             if (queue_empty) {
                                                 wright_in_process = false;
                                             }
                                         }
                                         if (!queue_empty) {
                                             do_write();
                                         }
                                     } else {
                                         spdlog::error("[TCP] TcpClient: Send failed {}", error.message());
                                     }
                                 });
    }

    void TcpClient::start_reading() {
        auto buffer = std::make_shared<boost::asio::streambuf>();
        socket_.async_read_some(buffer->prepare(1024),
                                [this, buffer](const boost::system::error_code& error, std::size_t bytes_transferred) {
                                    auto server_id = get_server_id();
                                    if (!error) {
                                        buffer->commit(bytes_transferred);
                                        std::istream is(buffer.get());
                                        std::string message;
                                        std::getline(is, message);
                                        spdlog::info("[TCP] TcpClient: Receive message from {}", server_id);
                                        spdlog::trace("[TCP] TcpClient: Received message: {}", message);

                                        start_reading();
                                    } else {
                                        spdlog::error("[TCP] TcpClient: Read failed {}", error.message());
                                    }
                                });
    }

    std::string TcpClient::get_server_id() const {
        return socket_.remote_endpoint().address().to_string() + ":" +
               std::to_string(socket_.remote_endpoint().port());
    }

    TcpClient::~TcpClient() {
        spdlog::info("[TCP] TcpClient: start destroying");
        if (socket_.is_open()) {
            boost::system::error_code ec;
            socket_.close(ec); // Close the socket

            if (ec) {
                spdlog::error("[TCP] TcpClient: Error while stopping the client: {}", ec.message());
            }
        }
        spdlog::info("[TCP] TcpClient: destroyed");
    }

} // namespace tcp