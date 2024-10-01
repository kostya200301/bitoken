//
// Created by Константин Беляков on 07.09.2024.
//

#include "BufferWorm.h"

namespace tcp {
    BufferWorm::BufferWorm(const std::string& client_id) : client_id_(client_id) {}

    void BufferWorm::add_buffer(const BufferPtr& buffer) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            buffers_.push_back(buffer);
        }
        read_all_jsons();
    }

    BufferPtr BufferWorm::get_buffer(size_t ind) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (buffers_.size() < ind) {
            // WARNING
            return nullptr;
        }
        return buffers_.at(ind);
    }

    void BufferWorm::read_all_jsons() {
        spdlog::info("[TCP] BufferWorm: start read JSONs for client: {}", client_id_);
        std::lock_guard<std::mutex> lock(mtx_);

        read_all();
    }

    ReadJSONStatus BufferWorm::read_all() {
        int buffers_size = buffers_.size();
        bool write = false;
        int last_i_end = -1;
        int last_j_end = -1;
        int last_i_start = -1;
        int last_j_start = -1;
        for (int i = 0; i < buffers_size; i++) {
            auto buf = buffers_.at(i)->get_boost_buffer()->data();
            auto begin = boost::asio::buffers_begin(buf);
            for (int j = 0; j < buf.size(); j++) {
                auto cur_el = *(begin + j);
                char next_el;
                if (j + 1 < buf.size()) {
                    next_el = *(begin + j + 1);
                } else {
                    if (i + 1 < buffers_size) {
                        auto begin_ = boost::asio::buffers_begin(buffers_.at(i + 1)->get_boost_buffer()->data());
                        next_el = *(begin_);
                    } else {
                        if (last_i_end != -1 && ((last_i_start < last_i_end) || ((last_i_start == last_i_end) && (last_j_start < last_j_end)))) {
                            for (int ind = 0; ind < last_i_end; ind++) {
                                buffers_.front()->finish_work();
                                buffers_.pop_front();
                            }
                            buffers_.front()->get_boost_buffer()->consume(last_j_end + 2);
                            return ReadJSONStatus::FoundAll;
                        } else if (last_i_end != -1 && ((last_i_start > last_i_end) || ((last_i_start == last_i_end) && (last_j_start > last_j_end)))) {
                            for (int ind = 0; ind < last_i_start; ind++) {
                                buffers_.front()->finish_work();
                                buffers_.pop_front();
                            }
                            buffers_.front()->get_boost_buffer()->consume(last_j_start);
                            return ReadJSONStatus::FoundAll;
                        }
                        if (last_i_end == -1) {
                            spdlog::info("DODELAT"); // DODELAT
                        }
                    }
//                    break;
                }


                if (cur_el == 'I' && next_el == '{') {
                    write = true;
                    last_i_start = i;
                    last_j_start = j;
                } else if (cur_el == '}' && next_el == 'I') {
                    if (write) {
                        last_i_end = i;
                        last_j_end = j;
                        std::string result;

                        if (last_i_start == last_i_end) {
                            auto bf = buffers_.at(last_i_start)->get_boost_buffer()->data();
                            result = std::string(boost::asio::buffers_begin(bf) + last_j_start + 1, boost::asio::buffers_begin(bf) + last_j_end + 1);
                        } else {
                            auto bf = buffers_.at(last_i_start)->get_boost_buffer()->data();
                            result = std::string(boost::asio::buffers_begin(bf) + last_j_start + 1, boost::asio::buffers_end(bf));
                            for (int ind_ = last_i_start + 1; ind_ < last_i_end; ind_++) {
                                auto bf2 = buffers_.at(ind_)->get_boost_buffer()->data();
                                result += std::string(boost::asio::buffers_begin(bf2), boost::asio::buffers_end(bf2));
                            }
                            if (last_i_start < last_i_end) {
                                auto bf3 = buffers_.at(last_i_end)->get_boost_buffer()->data();
                                result += std::string(boost::asio::buffers_begin(bf3), boost::asio::buffers_begin(bf3) + last_j_end + 1);
                            }

                        }

//                        spdlog::info("Mes: {}", result);
                        on_new_message_(client_id_, result); // убрать из лока
                    }
                    write = false;
                }
            }
        }
    }
}