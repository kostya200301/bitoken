//
// Created by Константин Беляков on 22.08.2024.
//

#ifndef BITOCEN_TCPSERVER_H
#define BITOCEN_TCPSERVER_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>
#include "tools/signal_slots.h"
#include "BuffersManager.h"

namespace tcp {

    class TcpServer;
    using TcpServerPtr = std::shared_ptr<TcpServer>;

    class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context, short port, const BuffersManagerPtr& buffers_manager);

        ~TcpServer();

        void start_accept();

    private:
        void handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                           const boost::system::error_code& error);

        void read_from_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

        void send_to_client(const std::string& client_id, const std::string& message);

        std::string get_client_id(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

        std::mutex mtx_;
        std::unordered_map<std::string, std::shared_ptr<boost::asio::ip::tcp::socket>> active_connections_;

        BuffersManagerPtr buffers_manager_;

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;

    };

} // namespace tcp


#endif //BITOCEN_TCPSERVER_H
