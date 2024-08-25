//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_MESSAGESMANAGER_H
#define BITOCEN_MESSAGESMANAGER_H

#include "MessagesQueue.h"
#include "tcp/TcpMessagesManager.h"

namespace model {

    class MessagesManager;
    using MessagesManagerPtr = std::shared_ptr<MessagesManager>;

    class MessagesManager {
    public:
        MessagesManager(const tcp::TcpMessagesManagerPtr& tcp_messages_manager);

        ~MessagesManager();

        IMessagePtr get_message() const;

        tcp::TcpClientPtr get_tcp_client() {
            return tcp_messages_manager_->get_tcp_client();
        }

        tcp::TcpMessagesManagerPtr get_tcp_messages_manager() {
            return tcp_messages_manager_;
        }

    private:
        tcp::TcpMessagesManagerPtr tcp_messages_manager_;
    };

}

#endif //BITOCEN_MESSAGESMANAGER_H
