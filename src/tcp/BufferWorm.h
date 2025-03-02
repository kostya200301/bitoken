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
#include "tcp_message_parts/TcpMessageParts.h"

namespace tcp {

    enum class ParseResult {
        OK,
        NotEnoughData,
        DataIsCorrupted
    };

    enum class ReadJSONStatus {
        FoundOne,
        FoundAll,
        FoundCorrupted,
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

        std::string get_client_id() {
            return client_id_;
        }

    public:
        INLINE_SIGNAL(new_message, void(const std::string& con_id, const TcpMessagePartsPtr& tcp_parts));

    private:
        std::string client_id_;

        std::mutex mtx_;
        std::deque<BufferPtr> buffers_;

        ReadJSONStatus read_one_json();

        ReadJSONStatus try_read_crazy_json();

        ReadJSONStatus read_all();

        ParseResult try_parse_s_part();

        ParseResult try_parse_i_part(const TcpMessageSPartPtr& s_part);

        ParseResult try_parse_d_part(const TcpMessageSPartPtr& s_part);

        void delete_until_new_block();

        void delete_n_chars(size_t n);

    private:
        TcpMessagePartsPtr parts_;
    };
}


#endif //BITOCEN_BUFFERWORM_H
