#include "MessagesQueue.h"

namespace model {

    MessagesQueue::MessagesQueue(const ThreadPoolManagerPtr& pool_manager) : pool_manager_(pool_manager) {}

    void MessagesQueue::enqueue(const IMessagePtr& message) {
        queue.push(message);
    }

    void MessagesQueue::enqueue(const std::string& con_id, const std::string& message) {
        pool_manager_->add_task([self = shared_from_this(), con_id, message]() {
            auto mes = make_message(con_id, message);
            if (mes != nullptr) {
                self->enqueue(mes);
            }
        });
    }

    IMessagePtr MessagesQueue::dequeue() {
        IMessagePtr mes;
        if (queue.try_pop(mes)) {
            return mes;
        }
        return nullptr;
    }

} // namespace model
