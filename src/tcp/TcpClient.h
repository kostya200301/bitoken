//
// Created by Константин Беляков on 23.08.2024.
//

#ifndef BITOCEN_TCPCLIENT_H
#define BITOCEN_TCPCLIENT_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>

namespace tcp {
    class TcpClient {
    public:
        TcpClient(boost::asio::io_context& io_context,
                  boost::asio::ssl::context& ssl_context,
                  const std::string& server,
                  short port);
        void start();
        void send_message(const std::string& message);

    private:
        void handle_handshake(const boost::system::error_code& error);
        void start_reading();

        std::string get_server_id() const;

        boost::asio::io_context& io_context_;
        boost::asio::ssl::context& ssl_context_;
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
        std::string server_;
        short port_;
    };
}


#endif //BITOCEN_TCPCLIENT_H
