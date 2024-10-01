//
// Created by Константин Беляков on 07.09.2024.
//

#ifndef BITOCEN_BUFFERSPOOL_H
#define BITOCEN_BUFFERSPOOL_H

#include "Buffer.h"
#include "unordered_map"
#include <spdlog/spdlog.h>


namespace tcp {

    class BuffersPool;
    using BuffersPoolPtr = std::shared_ptr<BuffersPool>;

    class BuffersPool {
    public:
        BuffersPool(int count);

        BufferPtr get_buffer();

        size_t get_free_buffers_count();

        size_t get_busy_buffers_count();

    private:
        std::mutex mtx_;
        std::unordered_map<size_t, BufferPtr> free_buffers_;
        std::unordered_map<size_t, BufferPtr> busy_buffers_;

        std::unordered_map<size_t, scoped_connection_ptr> buffer_slots_;

        void take_from_busy_put_to_free(size_t id);

        size_t last_buffer_id_;
        size_t init_size_;

    };
}




#endif //BITOCEN_BUFFERSPOOL_H
