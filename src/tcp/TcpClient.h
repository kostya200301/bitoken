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

    class TcpClient;
    using TcpClientPtr = std::shared_ptr<TcpClient>;

    class TcpClient {
    public:
        TcpClient(boost::asio::io_context& io_context,
                  const std::string& server,
                  short port);

        ~TcpClient();

        void start();

        void send_message(const std::string& message);

    private:
        void handle_connect(const boost::system::error_code& error);

        void start_reading();

        std::string get_server_id() const;

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::socket socket_;
        std::string server_;
        short port_;
    };

} // namespace tcp


#endif //BITOCEN_TCPCLIENT_H
