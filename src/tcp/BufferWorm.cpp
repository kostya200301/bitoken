//
// Created by Константин Беляков on 07.09.2024.
//

#include "BufferWorm.h"
#include <numeric>

namespace tcp {
    BufferWorm::BufferWorm(const std::string& client_id) : client_id_(client_id), parts_(nullptr) {}

    void BufferWorm::add_buffer(const BufferPtr& buffer) {
        std::lock_guard<std::mutex> lock(mtx_);
        buffers_.push_back(buffer);
//        read_all_jsons(); // Думаю надо тригерить какую то штуку которая будет в параллеле обрабатывать запросы
    }

    BufferPtr BufferWorm::get_buffer(size_t ind) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (buffers_.size() < ind) {
            // WARNING
            return nullptr;
        }
        return buffers_.at(ind);
    }

    void BufferWorm::read_all_jsons() { // WARN если сообщ очень большое (заявлено в S блоке) то добавить ему таймер
        spdlog::info("[TCP] BufferWorm: start read JSONs for client: {}", client_id_);
        {
//            std::lock_guard<std::mutex> lock(mtx_); // засунул в read_all чтобы сигнал не был под локом
            ReadJSONStatus status;
            while ((status = read_all()) == ReadJSONStatus::FoundAll || status == ReadJSONStatus::FoundCorrupted) {}
        }
    }

    ParseResult BufferWorm::try_parse_s_part() {
        int cur_buf_size = std::accumulate(buffers_.begin(), buffers_.end(), 0,
                                           [](int sum, const auto& buf) {
                                               return sum + buf->get_boost_buffer()->data().size();
                                           });
        if (cur_buf_size < TCPMessageSPartSIZE) {
            return ParseResult::NotEnoughData;
        }

        std::string info; // "S{000000000000}S"
        info.reserve(TCPMessageSPartSIZE);
        int cur_index = 0;
        while (info.size() < TCPMessageSPartSIZE) {
            auto buf = buffers_.at(cur_index)->get_boost_buffer()->data();
            auto begin = boost::asio::buffers_begin(buf);
            int gg = std::min(TCPMessageSPartSIZE - info.size(), buf.size());
            std::string part_result = std::string(begin, begin + gg);
            info += part_result;
            cur_index++;
        }
        if (info[0] != TCPMessageSPartBaseString[0] ||
            info[1] != TCPMessageSPartBaseString[1] ||
            info[TCPMessageSPartSIZE - 2] != TCPMessageSPartBaseString[TCPMessageSPartSIZE - 2] ||
            info[TCPMessageSPartSIZE - 1] != TCPMessageSPartBaseString[TCPMessageSPartSIZE - 1]) {
            return ParseResult::DataIsCorrupted;
        }
        parts_->set_s_part(std::make_shared<TcpMessageSPart>(std::stoi(info.substr(2, 6)), std::stoi(info.substr(8, 6))));
        return ParseResult::OK;
    }

    ParseResult BufferWorm::try_parse_i_part(const TcpMessageSPartPtr& s_part) {
        int cur_buf_size = std::accumulate(buffers_.begin(), buffers_.end(), 0,
                                           [](int sum, const auto& buf) {
                                               return sum + buf->get_boost_buffer()->data().size();
                                           });
        if (cur_buf_size < s_part->get_info_part_size()) {
            return ParseResult::NotEnoughData;
        }

        std::string data;
        data.reserve(s_part->get_info_part_size());
        int cur_index = 0;
        while (data.size() < s_part->get_info_part_size()) {
            auto buf = buffers_.at(cur_index)->get_boost_buffer()->data();
            auto begin = boost::asio::buffers_begin(buf);
            int gg = std::min(s_part->get_info_part_size() - data.size(), buf.size());
            std::string part_result = std::string(begin, begin + gg);
            data += part_result;
            cur_index++;
        }
        if (data[0] != 'I' || data[1] != '{' || data[data.size() - 2] != '}' || data[data.size() - 1] != 'I') {
            return ParseResult::DataIsCorrupted;
        }
        parts_->set_i_part(std::make_shared<TcpMessageIPart>(data));
        return ParseResult::OK;
    }

    ParseResult BufferWorm::try_parse_d_part(const TcpMessageSPartPtr& s_part) {
        int cur_buf_size = std::accumulate(buffers_.begin(), buffers_.end(), 0,
                                           [](int sum, const auto& buf) {
                                               return sum + buf->get_boost_buffer()->data().size();
                                           });
        if (cur_buf_size < s_part->get_data_part_size()) {
            return ParseResult::NotEnoughData;
        }

        std::string data;
        data.reserve(s_part->get_data_part_size());
        int cur_index = 0;
        while (data.size() < s_part->get_data_part_size()) {
            auto buf = buffers_.at(cur_index)->get_boost_buffer()->data();
            auto begin = boost::asio::buffers_begin(buf);
            int gg = std::min(s_part->get_data_part_size() - data.size(), buf.size());
            std::string part_result = std::string(begin, begin + gg);
            data += part_result;
            cur_index++;
        }
        if (data[0] != 'D' || data[1] != '{' || data[data.size() - 2] != '}' || data[data.size() - 1] != 'D') {
            return ParseResult::DataIsCorrupted;
        }
        parts_->set_d_part(std::make_shared<TcpMessageDPart>(data));
        return ParseResult::OK;
    }

    void BufferWorm::delete_until_new_block() {
        for (int i = 0; i < buffers_.size(); i++) {
            auto buf = buffers_.at(i)->get_boost_buffer()->data();
            auto begin = boost::asio::buffers_begin(buf);
            for (int j = 0; j < buf.size(); j++) {
                if (*(begin + j) == 'S' &&
                        ((j + 1 < buf.size() && *(begin + j + 1) == '{') ||
                        ((i + 1 < buffers_.size()) && (*boost::asio::buffers_begin(buffers_.at(i + 1)->get_boost_buffer()->data())) == '{'))) {
                    for (int ind = 0; ind < i; ind++) {
                        buffers_.front()->finish_work();
                        buffers_.pop_front();
                    }
                    buffers_.front()->get_boost_buffer()->consume(j);
                    return;
                }
            }
        }

    }

    void BufferWorm::delete_n_chars(size_t n) {
        int cur_size = 0;
        while (cur_size < n) {
            auto buf = buffers_.front()->get_boost_buffer()->data();
            if (cur_size + buf.size() <= n) {
                cur_size += buf.size();
                buffers_.front()->finish_work();
                buffers_.pop_front();
            } else {
                buffers_.front()->get_boost_buffer()->consume(n - cur_size);
                return;
            }
        }
    }


    ReadJSONStatus BufferWorm::read_all() { // WARN переделать так, чтобы не было привязки к бустовому буферу
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (parts_ == nullptr || parts_->get_s_part() == nullptr) {
                delete_until_new_block();

                parts_ = std::make_shared<TcpMessageParts>();
                auto S_result = try_parse_s_part();
                if (S_result == ParseResult::DataIsCorrupted) {
                    delete_n_chars(2);
                    return ReadJSONStatus::FoundAll;
                } else if (S_result == ParseResult::NotEnoughData) {
                    return ReadJSONStatus::FoundPart;
                }
                delete_n_chars(TCPMessageSPartSIZE);
            }

            if (parts_->get_i_part() == nullptr) {
                auto I_result = try_parse_i_part(parts_->get_s_part());
                if (I_result == ParseResult::DataIsCorrupted) {
                    delete_until_new_block();
                    parts_ = nullptr;
                    return ReadJSONStatus::FoundCorrupted;
                }
                else if (I_result == ParseResult::NotEnoughData) {
                    return ReadJSONStatus::FoundPart;
                }
                delete_n_chars(parts_->get_s_part()->get_info_part_size());
            }

            if (parts_->get_d_part() == nullptr) {
                auto D_result = try_parse_d_part(parts_->get_s_part());
                if (D_result == ParseResult::DataIsCorrupted) {
                    delete_until_new_block();
                    parts_ = nullptr;
                    return ReadJSONStatus::FoundCorrupted;
                }
                else if (D_result == ParseResult::NotEnoughData) {
                    return ReadJSONStatus::FoundPart;
                }
                delete_n_chars(parts_->get_s_part()->get_data_part_size());
            }

            spdlog::info("!!! {} !!! NEW MESSAGE {}", client_id_, parts_->get_d_part()->get_data().substr(1, parts_->get_d_part()->get_data().size() - 2).size());
//            on_new_message_(client_id_, parts_->get_d_part()->get_data().substr(1, parts_->get_d_part()->get_data().size() - 2)); // WARN убрать из лока
            on_new_message_(client_id_, parts_); // WARN убрать из лока
            parts_ = nullptr;
        }

        return ReadJSONStatus::FoundAll;
    }
}