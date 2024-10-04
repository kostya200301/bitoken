//
// Created by Константин Беляков on 07.09.2024.
//

#ifndef BITOCEN_BUFFERWORM_H
#define BITOCEN_BUFFERWORM_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <string>
#include <deque>
#include <spdlog/spdlog.h>
#include "Buffer.h"

namespace tcp {

    enum class ReadJSONStatus {
        FoundOne,
        FoundAll,
        FoundPart,
        NothingFound
    };

    class BufferWorm;
    using BufferWormPtr = std::shared_ptr<BufferWorm>;

    class BufferWorm {
    public:
        BufferWorm(const std::string& client_id);

        void add_buffer(const BufferPtr& buffer);

        BufferPtr get_buffer(size_t ind);

        void read_all_jsons();

    public:
        INLINE_SIGNAL(new_message, void(const std::string& con_id, const std::string& mes));

    private:
        std::string client_id_;

        std::mutex mtx_;
        std::deque<BufferPtr> buffers_;

        ReadJSONStatus read_one_json();

        ReadJSONStatus try_read_crazy_json();

        ReadJSONStatus read_all();
    };
}


#endif //BITOCEN_BUFFERWORM_H
