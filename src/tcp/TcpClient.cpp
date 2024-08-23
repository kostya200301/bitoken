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
                         boost::asio::ssl::context& ssl_context,
                         const std::string& server,
                         short port)
            : io_context_(io_context),
              ssl_context_(ssl_context),
              socket_(io_context, ssl_context),
              server_(server),
              port_(port) {
    }

    void TcpClient::start() {
        boost::asio::ip::tcp::resolver resolver(io_context_);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(server_, std::to_string(port_));

        boost::asio::async_connect(socket_.lowest_layer(), endpoints,
                                   [this](const boost::system::error_code& error, const boost::asio::ip::tcp::endpoint&) {
                                       if (!error) {
                                           socket_.async_handshake(boost::asio::ssl::stream_base::client,
                                                                   [this](const boost::system::error_code& handshake_error) {
                                                                       handle_handshake(handshake_error);
                                                                   });
                                       } else {
                                           spdlog::error("[TCP] TcpClient: Connect failed {}", error.message());
                                       }
                                   });
    }

    void TcpClient::handle_handshake(const boost::system::error_code& error) {
        if (!error) {
            spdlog::info("[TCP] TcpClient: TLS handshake succeeded");
            start_reading(); // Start reading from server
            send_message("Hello, server!"); // Send initial message
        } else {
            spdlog::error("[TCP] TcpClient: TLS handshake failed {}", error.message());
        }
    }

    void TcpClient::send_message(const std::string& message) {
        auto buffer = std::make_shared<std::string>(message);
        boost::asio::async_write(socket_, boost::asio::buffer(*buffer),
                                 [this, buffer](const boost::system::error_code& error, std::size_t) {
                                     if (!error) {
                                         spdlog::info("[TCP] TcpClient: Send message to {}", get_server_id());
                                         spdlog::trace("[TCP] TcpClient: Sent message {}", *buffer);
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
        return socket_.lowest_layer().remote_endpoint().address().to_string() + ":" +
               std::to_string(socket_.lowest_layer().remote_endpoint().port());
    }

} // namespace tcp