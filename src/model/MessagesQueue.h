// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_MESSAGESQUEUE_H
#define BITOCEN_MESSAGESQUEUE_H

#include <memory>
#include <atomic>
#include <string>
#include "Messages/IMessage.h"
#include "PoolManager.h"
#include <spdlog/spdlog.h>
#include "concurrentqueue.h"
#include "tcp/tcp_message_parts/TcpMessageParts.h"


namespace model {

    class MessagesQueue;
    using MessagesQueuePtr = std::shared_ptr<MessagesQueue>;

    class MessagesQueue : public std::enable_shared_from_this<MessagesQueue> {
    public:
        explicit MessagesQueue(const ThreadPoolManagerPtr& pool_manager);

        ~MessagesQueue();

        void enqueue(const IMessagePtr& message);
        void enqueue(const std::string& con_id, const std::string& message);
        void enqueue(const std::string& con_id, const tcp::TcpMessagePartsPtr& tcp_parts);
        int get_size_approx() const;
        IMessagePtr dequeue();

    private:
        ThreadPoolManagerPtr pool_manager_;

        moodycamel::ConcurrentQueue<IMessagePtr> queue;

    };

} // namespace model

#endif // BITOCEN_MESSAGESQUEUE_H
