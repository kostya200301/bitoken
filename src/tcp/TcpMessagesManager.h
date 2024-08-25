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

namespace tcp {


    class TcpMessagesManager;
    using TcpMessagesManagerPtr = std::shared_ptr<TcpMessagesManager>;

    class TcpMessagesManager : public std::enable_shared_from_this<TcpMessagesManager> {
    public:
        explicit TcpMessagesManager(const model::MessagesQueuePtr& messages_queue);

        ~TcpMessagesManager();

        void init();

        void stop();

//        void new_message(const std::string& con_id);

        model::MessagesQueuePtr get_messages_queue() {
            return messages_queue_;
        }

        tcp::TcpClientPtr get_tcp_client() {
            return tcp_client_;
        }

    private:

        void start_client();

        void start_server();

        model::MessagesQueuePtr messages_queue_;

        bool initial = false;

        boost::asio::io_context io_context_client;
        boost::asio::io_context io_context_server;

        scoped_connection_ptr new_messages_slot;

        std::unique_ptr<std::thread> io_thread_client;
        std::unique_ptr<std::thread> io_thread_server;

        // IMPORTANT after contexts and threads!!
        TcpClientPtr tcp_client_;
        TcpServerPtr tcp_server_;
    };

}


#endif //BITOCEN_TCPMESSAGESMANAGER_H
