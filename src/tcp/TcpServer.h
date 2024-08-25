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

namespace tcp {

    enum class ReadJSONStatus {
        FoundAll,
        FoundPart,
        NothingFound
    };

    class TcpServer;
    using TcpServerPtr = std::shared_ptr<TcpServer>;

    class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context, short port);


        ~TcpServer();

        void start_accept();

    public:
        INLINE_SIGNAL(new_message, void(const std::string& con_id, const std::string& mes));

    private:
        void handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                           const boost::system::error_code& error);

        void read_from_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

        void send_to_client(const std::string& client_id, const std::string& message);

        void add_stream_buf(const std::string& con_id);

        void del_stream_buf(const std::string& con_id);

        int get_stream_buf_length(const std::string& con_id);

        void new_message(const std::string& con_id);

        void handle_message(const std::string& con_id);

        std::shared_ptr<boost::asio::streambuf> get_stream_buf(const std::string& con_id);

        ReadJSONStatus read_one_json(const std::string& con_id);

        std::string get_client_id(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

        void close_all_connections();


        std::mutex mtx_;
        std::unordered_map<std::string, std::shared_ptr<boost::asio::ip::tcp::socket>> active_connections_;

        std::mutex mtx_buffers_;
        std::unordered_map<std::string, std::shared_ptr<boost::asio::streambuf>> buffers_;

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;

    };

} // namespace tcp


#endif //BITOCEN_TCPSERVER_H
