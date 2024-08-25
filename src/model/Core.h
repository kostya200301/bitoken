//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_CORE_H
#define BITOCEN_CORE_H

#include "PoolManager.h"
#include "MessagesQueue.h"
#include "tcp/TcpMessagesManager.h"
#include "MessagesManager.h"

namespace model {

    class Core {
    public:
        Core() {};

        void configure();

        model::MessagesManagerPtr get_messages_manager() {
            return messages_manager_;
        }

        tcp::TcpMessagesManagerPtr get_tcp_manager_mes() {
            return tcp_manager_mes_;
        }

        model::MessagesQueuePtr get_messages_queue() {
            return messages_queue_;
        }

        model::ThreadPoolManagerPtr get_pool_manager() {
            return pool_manager_;
        }

    private:
        model::MessagesManagerPtr messages_manager_;
        model::ThreadPoolManagerPtr pool_manager_;
        model::MessagesQueuePtr messages_queue_;
        tcp::TcpMessagesManagerPtr tcp_manager_mes_;
    };

}

#endif //BITOCEN_CORE_H
