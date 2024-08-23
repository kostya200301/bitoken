//
// Created by Константин Беляков on 22.08.2024.
//

#include "TcpServer.h"
#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>
#include <spdlog/spdlog.h>

namespace tcp {

    TcpServer::TcpServer(boost::asio::io_context& io_context,
                         boost::asio::ssl::context& ssl_context,
                         short port)
            : io_context_(io_context),
              ssl_context_(ssl_context),
              acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    }

    void TcpServer::start_accept() {
        auto socket = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(io_context_, ssl_context_);
        acceptor_.async_accept(socket->lowest_layer(),
                               [this, socket](const boost::system::error_code& error) {
                                   handle_accept(socket, error);
                               });
    }

    void TcpServer::handle_accept(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
                                  const boost::system::error_code& error) {
        if (!error) {
            auto client_id = get_client_id(socket);
            {
                std::lock_guard<std::mutex> lock(mtx_);
                active_connections_[client_id] = socket;
            }

            spdlog::info("[TCP] TcpServer: add user: {}", client_id);

            socket->async_handshake(boost::asio::ssl::stream_base::server,
                                    [this, socket](const boost::system::error_code& handshake_error) {
                                        if (!handshake_error) {
                                            spdlog::info("[TCP] TcpServer: TLS handshake succeeded");
                                            read_from_client(socket); // Start reading from client
                                        } else {
                                            spdlog::error("[TCP] TcpServer: TLS handshake failed: {}", handshake_error.message());
                                        }
                                    });
        } else {
            spdlog::error("[TCP] TcpServer: Accept failed: {}", error.message());
        }
        start_accept();
    }

    void TcpServer::handle_client_connection(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
                                             const boost::system::error_code& error) {
        if (!error) {
            socket->async_handshake(boost::asio::ssl::stream_base::server,
                                    [socket, this](const boost::system::error_code& handshake_error) {
                                        if (!handshake_error) {
                                            spdlog::info("[TCP] TcpServer: Client connected and TLS handshake succeeded");
                                            read_from_client(socket);
                                        } else {
                                            spdlog::error("[TCP] TcpServer: TLS handshake failed: {}", handshake_error.message());
                                        }
                                    });
        } else {
            spdlog::error("[TCP] TcpServer: Client connection failed: {}", error.message());
        }
    }

    void TcpServer::read_from_client(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket) {
        auto buffer = std::make_shared<boost::asio::streambuf>();
        socket->async_read_some(buffer->prepare(1024),
                                [this, socket, buffer](const boost::system::error_code& error, std::size_t bytes_transferred) {
                                    std::string client_id = get_client_id(socket);
                                    if (!error) {
                                        buffer->commit(bytes_transferred);
                                        std::istream is(buffer.get());
                                        std::string message;
                                        std::getline(is, message);
                                        spdlog::info("[TCP] TcpServer: Receive message from {}", client_id);
                                        spdlog::trace("[TCP] TcpServer: Received message: {}", message);
                                        read_from_client(socket);
                                    } else {
                                        {
                                            std::lock_guard<std::mutex> lock(mtx_);
                                            active_connections_.erase(client_id);
                                        }
                                        spdlog::info("[TCP] TcpServer: TcpServer: del user: {}", client_id);

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

    std::string TcpServer::get_client_id(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket) {
        return socket->lowest_layer().remote_endpoint().address().to_string() + ":" +
               std::to_string(socket->lowest_layer().remote_endpoint().port());
    }

}

