// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_MESSAGESQUEUE_H
#define BITOCEN_MESSAGESQUEUE_H

#include <memory>
#include <atomic>
#include "Messages/IMessage.h"
#include "PoolManager.h"
#include <spdlog/spdlog.h>
#include <tbb/concurrent_queue.h>


namespace model {

    class MessagesQueue;
    using MessagesQueuePtr = std::shared_ptr<MessagesQueue>;

    class MessagesQueue : public std::enable_shared_from_this<MessagesQueue> {
    public:
        explicit MessagesQueue(const ThreadPoolManagerPtr& pool_manager);

        void enqueue(const IMessagePtr& message);
        void enqueue(const std::string& con_id, const std::string& message);
        IMessagePtr dequeue();

    private:
        ThreadPoolManagerPtr pool_manager_;

        tbb::concurrent_queue<IMessagePtr> queue;

    };

} // namespace model

#endif // BITOCEN_MESSAGESQUEUE_H
