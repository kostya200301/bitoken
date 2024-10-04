//
// Created by Константин Беляков on 07.09.2024.
//

#ifndef BITOCEN_BUFFER_H
#define BITOCEN_BUFFER_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>
#include "tools/signal_slots.h"
#include <spdlog/spdlog.h>


namespace tcp {
    class Buffer;
    using BufferPtr = std::shared_ptr<Buffer>;

    class Buffer {
    public:
        Buffer(size_t id) : id_(id) {
            spdlog::info("[TCP] Buffer: create id = {}", id);
            buffer_ = std::make_shared<boost::asio::streambuf>();
        }

        Buffer() : id_(-1) {
            spdlog::info("[TCP] Buffer: create id");
            buffer_ = std::make_shared<boost::asio::streambuf>();
        }

        std::shared_ptr<boost::asio::streambuf> get_boost_buffer() {
            return buffer_;
        }

        void finish_work();

        size_t get_id() {
            return id_;
        }

    public:
        INLINE_SIGNAL(finish_work, void());

    private:
        std::shared_ptr<boost::asio::streambuf> buffer_;
        size_t id_;
    };
}

#endif //BITOCEN_BUFFER_H
