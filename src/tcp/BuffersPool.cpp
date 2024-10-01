//
// Created by Константин Беляков on 07.09.2024.
//

#include "BuffersPool.h"
#include "iostream"

namespace tcp {
    BuffersPool::BuffersPool(int count) {
        for (int i = 0; i < count; i++) {
            free_buffers_[i] = std::make_shared<Buffer>(i);
            buffer_slots_[i] = free_buffers_[i]->on_finish_work_slot([&, i] () {
                take_from_busy_put_to_free(i);
            });
        }
        last_buffer_id_ = count - 1;
        init_size_ = count;
        spdlog::info("[TCP] BuffersPool: create size = {}", count);
    }

    BufferPtr BuffersPool::get_buffer() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!free_buffers_.empty()) {
            auto it = free_buffers_.begin();
            BufferPtr value = it->second;
            busy_buffers_[it->first] = value;
            free_buffers_.erase(it);
            spdlog::trace("[TCP] BuffersPool: get buffer");
            return value;
        }

        spdlog::trace("[TCP] BuffersPool: create new buffer");
        last_buffer_id_++;
        size_t id = last_buffer_id_;
        busy_buffers_[id] = std::make_shared<Buffer>(id);
        buffer_slots_[id] = busy_buffers_[id]->on_finish_work_slot([&, id] () {
            take_from_busy_put_to_free(id);
        });
        return busy_buffers_[id];
    }

    void BuffersPool::take_from_busy_put_to_free(size_t id) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = busy_buffers_.find(id);
        if (it != busy_buffers_.end()) {
            auto value = it->second;
            value->get_boost_buffer()->consume(value->get_boost_buffer()->size());
            busy_buffers_.erase(it);
            free_buffers_[id] = value;
        } else {
            spdlog::warn("[TCP] BuffersPool: take_from_busy_put_to_free buffer {} not found in busy_buffers_", id);
            return;
        }
        // Если становится очень много, то надо удалять
    }

    size_t BuffersPool::get_free_buffers_count() {
        std::lock_guard<std::mutex> lock(mtx_);
        return free_buffers_.size();
    }

    size_t BuffersPool::get_busy_buffers_count() {
        std::lock_guard<std::mutex> lock(mtx_);
        return busy_buffers_.size();
    }
}