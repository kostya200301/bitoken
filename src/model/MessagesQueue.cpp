#include "MessagesQueue.h"
#include <spdlog/spdlog.h>

namespace model {

    MessagesQueue::MessagesQueue(const ThreadPoolManagerPtr& pool_manager) : pool_manager_(pool_manager) {
        spdlog::info("[MODEL] MessagesQueue: create");
    }

    void MessagesQueue::enqueue(const IMessagePtr& message) {
        queue.enqueue(message);
    }

    void MessagesQueue::enqueue(const std::string& con_id, const std::string& message) {
        auto mes = make_message(con_id, message);
        if (mes != nullptr) {
            enqueue(mes);
        }
    }

    void MessagesQueue::enqueue(const std::string& con_id, const tcp::TcpMessagePartsPtr& tcp_parts) {
        auto mes = make_message(con_id, tcp_parts);
        if (mes != nullptr) {
            enqueue(mes);
        }
    }

    IMessagePtr MessagesQueue::dequeue() {
        IMessagePtr mes;
        return queue.try_dequeue(mes) ? mes : nullptr;
    }

    int MessagesQueue::get_size_approx() const {
        return queue.size_approx();
    }

    MessagesQueue::~MessagesQueue() {
        spdlog::info("[MODEL] MessagesQueue: destroyed");
    }

} // namespace model
