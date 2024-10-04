//
// Created by Константин Беляков on 07.09.2024.
//

#include "BuffersPool.h"
#include "iostream"
#include <random>

// Мьютексы не нужны так как работа тут происходит асинхронно только

namespace tcp {
    BuffersPool::BuffersPool(int count) {
        std::lock_guard<std::mutex> lock(mtx_);
        for (int i = 0; i < count; i++) {
            auto buf = std::make_shared<Buffer>(cur_id_);
            buffers_.push(buf);
            buffer_slots_[cur_id_] = buf->on_finish_work_slot([&, buf] () {
                spdlog::warn("[TCP] BuffersPool: on finish work");
                take_from_busy_put_to_free(buf);
            });
            cur_id_++;
        }
        init_size_ = count;
        spdlog::info("[TCP] BuffersPool: create size = {}", count);
    }

    BufferPtr BuffersPool::get_buffer() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!buffers_.empty()) {
            auto buf = buffers_.front(); // могут ли два чувака долбиться в один??
            buffers_.pop();
            spdlog::info("[TCP] BuffersPool: get buffer");
            return buf;
        }

        spdlog::trace("[TCP] BuffersPool: create new buffer");
        auto buf = std::make_shared<Buffer>(cur_id_);
        buffer_slots_[cur_id_] = buf->on_finish_work_slot([&, buf] () {
            spdlog::warn("[TCP] BuffersPool: on finish work");
            take_from_busy_put_to_free(buf);
        });
        cur_id_++;
        return buf;
    }

    void BuffersPool::take_from_busy_put_to_free(const std::shared_ptr<Buffer>& buf) {
        std::lock_guard<std::mutex> lock(mtx_); // NOOOOOY
        buf->get_boost_buffer()->consume(buf->get_boost_buffer()->size());
        buffers_.push(buf);

        if (buffers_.size() > 4 * init_size_) {
            spdlog::warn("[TCP] BuffersPool: clear memory, size_bef={}, size_aft={}", buffers_.size(), buffers_.size() - buffers_.size() / 2);
            for (int i = 0; i < buffers_.size() / 2; i++) {
                auto buffer = buffers_.front();
                buffers_.pop();
                buffer_slots_.erase(buffer->get_id());
            }
        }

    }

    size_t BuffersPool::get_free_buffers_count() {
        std::lock_guard<std::mutex> lock(mtx_);
        return buffers_.size();
    }
}