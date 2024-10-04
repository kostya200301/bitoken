//
// Created by Константин Беляков on 07.09.2024.
//

#ifndef BITOCEN_BUFFERSPOOL_H
#define BITOCEN_BUFFERSPOOL_H

#include "Buffer.h"
#include "queue"
#include <spdlog/spdlog.h>


namespace tcp {

    class BuffersPool;
    using BuffersPoolPtr = std::shared_ptr<BuffersPool>;

    class BuffersPool {
    public:
        BuffersPool(int count);

        BufferPtr get_buffer();

        size_t get_free_buffers_count();

    private:
        std::mutex mtx_;
        std::queue<BufferPtr> buffers_;

        std::unordered_map<size_t, scoped_connection_ptr> buffer_slots_;

        void take_from_busy_put_to_free(const std::shared_ptr<Buffer>& buf);

        size_t init_size_;
        size_t cur_id_ = 0;

    };
}




#endif //BITOCEN_BUFFERSPOOL_H
