//
// Created by Константин Беляков on 22.08.2024.
//

#ifndef BITOCEN_TCPSERVER_H
#define BITOCEN_TCPSERVER_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>

namespace tcp {
    class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context,
                  boost::asio::ssl::context& ssl_context,
                  short port);
        void start_accept();

    private:
        void handle_accept(const boost::system::error_code& error);
        void handle_client_connection(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
                                      const boost::system::error_code& error);

        boost::asio::io_context& io_context_;
        boost::asio::ssl::context& ssl_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
    };
}


#endif //BITOCEN_TCPSERVER_H
