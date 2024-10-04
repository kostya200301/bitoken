//
// Created by Константин Беляков on 07.09.2024.
//

#ifndef BITOCEN_BUFFERSMANAGER_H
#define BITOCEN_BUFFERSMANAGER_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>
#include <list>
#include "Buffer.h"
#include "BuffersPool.h"
#include "BufferWorm.h"
#include "model/MessagesQueue.h"
#include <spdlog/spdlog.h>

namespace tcp {

    class BuffersManager;
    using BuffersManagerPtr = std::shared_ptr<BuffersManager>;

    class BuffersManager {
    public:
        BuffersManager(const BuffersPoolPtr& buffer_pool, const model::MessagesQueuePtr& messages_queue, size_t threads_count);

        void add_new_buffer(const std::string& client_id, const BufferPtr& buffer);

        void add_new_client(const std::string& client_id);

        void del_client(const std::string& client_id);

        BufferPtr get_buffer();

    private:

        std::mutex mtx_;
        std::unordered_map<std::string, BufferWormPtr> buffers_;
        std::unordered_map<std::string, scoped_connection_ptr> buffers_slots_;

        model::ThreadPoolManagerPtr threads_pool_;

        model::MessagesQueuePtr messages_queue_;

        BuffersPoolPtr buffer_pool_;

    };
}



#endif //BITOCEN_BUFFERSMANAGER_H
