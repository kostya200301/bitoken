//
// Created by Константин Беляков on 24.08.2024.
//

#include "MessagesManager.h"
#include <spdlog/spdlog.h>


namespace model {

    MessagesManager::MessagesManager(const tcp::TcpMessagesManagerPtr& tcp_messages_manager)
                        : tcp_messages_manager_(tcp_messages_manager) {
        spdlog::info("[MODEL] MessagesManager: create");
    }

    IMessagePtr MessagesManager::get_message() const {
        return tcp_messages_manager_->get_messages_queue()->dequeue();
    }

    MessagesManager::~MessagesManager() {
        spdlog::info("[MODEL] MessagesManager: destroyed");
    }

}