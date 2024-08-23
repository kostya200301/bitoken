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

        void send_to_client(const std::string& client_id, const std::string& message);


    private:
        void handle_accept(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket, const boost::system::error_code& error);
        void handle_client_connection(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
                                      const boost::system::error_code& error);
        void read_from_client(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket);

        std::string get_client_id(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket);

        boost::asio::io_context& io_context_;
        boost::asio::ssl::context& ssl_context_;
        boost::asio::ip::tcp::acceptor acceptor_;

        std::mutex mtx_;
        std::unordered_map<std::string, std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>> active_connections_;
    };
}


#endif //BITOCEN_TCPSERVER_H
