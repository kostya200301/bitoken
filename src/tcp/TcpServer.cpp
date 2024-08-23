//
// Created by Константин Беляков on 22.08.2024.
//

#include "TcpServer.h"
#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>

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
                                   handle_accept(error);
                               });
    }

    void TcpServer::handle_accept(const boost::system::error_code& error) {
        if (!error) {
            auto socket = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(io_context_, ssl_context_);
            acceptor_.async_accept(socket->lowest_layer(),
                                   [this, socket](const boost::system::error_code& error) {
                                       handle_client_connection(socket, error);
                                   });
        } else {
            std::cerr << "Accept failed: " << error.message() << std::endl;
        }
    }

    void TcpServer::handle_client_connection(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
                                             const boost::system::error_code& error) {
        if (!error) {
            socket->async_handshake(boost::asio::ssl::stream_base::server,
                                    [socket](const boost::system::error_code& handshake_error) {
                                        if (!handshake_error) {
                                            std::cout << "Client connected and TLS handshake succeeded." << std::endl;
                                            // Here you can start reading/writing data with the socket.
                                        } else {
                                            std::cerr << "TLS handshake failed: " << handshake_error.message() << std::endl;
                                        }
                                    });
        } else {
            std::cerr << "Client connection failed: " << error.message() << std::endl;
        }
    }

}

