//
// Created by Константин Беляков on 24.08.2024.
//

#include "MessagesManager.h"

namespace model {

    MessagesManager::MessagesManager(const tcp::TcpMessagesManagerPtr& tcp_messages_manager)
                        : tcp_messages_manager_(tcp_messages_manager) {

    }

    IMessagePtr MessagesManager::get_message() const {
        return tcp_messages_manager_->get_messages_queue()->dequeue();
    }

}