//
// Created by Константин Беляков on 07.09.2024.
//

#include "BuffersManager.h"


namespace tcp {

    BuffersManager::BuffersManager(const BuffersPoolPtr& buffer_pool, const model::MessagesQueuePtr& messages_queue, size_t threads_count) : buffer_pool_(buffer_pool), messages_queue_(messages_queue) {
        threads_pool_ = std::make_shared<model::ThreadPoolManager>(); // WARN
        threads_pool_->start_threads_pool(threads_count);
    }

    void BuffersManager::add_new_buffer(const std::string& client_id, const BufferPtr& buffer) {
        auto it = buffers_.find(client_id);
        if (it != buffers_.end()) {
            auto buffer_worm = it->second;
            buffer_worm->add_buffer(buffer);

            threads_pool_->add_task([buffer_worm] () {
                buffer_worm->read_all_jsons();
            });

        } else {
            // WARNING
        }

    }

    BufferPtr BuffersManager::get_buffer() {
        return buffer_pool_->get_buffer();
    }

    void BuffersManager::add_new_client(const std::string& client_id) {
//        std::lock_guard<std::mutex> lock(mtx_); // Думаю тут тоже асинхранность и не надо
        buffers_[client_id] = std::make_shared<BufferWorm>(client_id);
        buffers_slots_[client_id] = buffers_[client_id]->on_new_message_slot([this](const std::string& con_id, const std::string& mes) {
            messages_queue_->enqueue(con_id, mes);
        });
    }

    void BuffersManager::del_client(const std::string& client_id) {
//        std::lock_guard<std::mutex> lock(mtx_); // Думаю тут тоже асинхранность и не надо
        buffers_.erase(client_id);
        buffers_slots_.erase(client_id);
    }

}