//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_TCPMESSAGESMANAGER_H
#define BITOCEN_TCPMESSAGESMANAGER_H

#include <unordered_map>
#include <boost/asio.hpp>
#include "tools/signal_slots.h"
#include "model/MessagesQueue.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include "BuffersManager.h"

namespace tcp {


    class TcpMessagesManager;
    using TcpMessagesManagerPtr = std::shared_ptr<TcpMessagesManager>;

    class TcpMessagesManager : public std::enable_shared_from_this<TcpMessagesManager> {
    public:
        explicit TcpMessagesManager(model::MessagesQueuePtr  messages_queue, size_t server_port, size_t threads_count);

        ~TcpMessagesManager();

        void init();

        void stop();

//        void new_message(const std::string& con_id);

        model::MessagesQueuePtr get_messages_queue() {
            return messages_queue_;
        }

        tcp::TcpClientPtr get_tcp_client(const std::string& id) {
            auto it = tcp_clients_.find(id);
            if (it != tcp_clients_.end()) {
                return it->second;
            }
            return nullptr;
        }

        tcp::TcpClientPtr add_tcp_client(const std::string & host, int port, const std::string& data);

    private:

        void start_client(const std::string& id);

        void start_server();

        model::MessagesQueuePtr messages_queue_;

        bool initial = false;

        bool io_context_client_act = false;
        boost::asio::io_context io_context_client_;
        boost::asio::io_context io_context_server_;

        BuffersManagerPtr buffers_manager_;
        BuffersPoolPtr buffers_pool_;

        std::unordered_map<std::string, std::unique_ptr<std::thread>> io_thread_clients_;
        std::unique_ptr<std::thread> io_thread_server;

        // IMPORTANT after contexts and threads!!
        std::unordered_map<std::string, TcpClientPtr> tcp_clients_;
        TcpServerPtr tcp_server_;
    };

}


#endif //BITOCEN_TCPMESSAGESMANAGER_H
