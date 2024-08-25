#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpClient.h"
#include "tcp/TcpMessagesManager.h"
#include "crypto/CryptoHelper.h"
#include "model/MessagesQueue.h"
#include "model/PoolManager.h"

void add_data_in_buffer(std::shared_ptr<boost::asio::streambuf> buffer, const std::string& data) {
    std::ostream os(&*buffer);
    os << data;
}

TEST_CASE("Test tcp messages manager", "[model][unit][coverage]") {
    model::ThreadPoolManagerPtr pool_manager = std::make_shared<model::ThreadPoolManager>();
    pool_manager->start_threads_pool(5);
    auto messages_queue = std::make_shared<model::MessagesQueue>(pool_manager);
    tcp::TcpMessagesManager manager(messages_queue);

//    manager.add_stream_buf("lalipop");
//
//    auto buf = manager.get_stream_buf("lalipop");
//
//    add_data_in_buffer(buf, "{text123123123}");
//    manager.new_message("lalipop");
//    CHECK(!manager.get_stream_buf_length("lalipop"));
//
//    add_data_in_buffer(buf, "qweqwe{text123123123}eqwe}Iwq");
//    manager.new_message("lalipop");
//    CHECK(!manager.get_stream_buf_length("lalipop"));
//
//    add_data_in_buffer(buf, "I{gooddata}I");
//    manager.new_message("lalipop");
//    CHECK(!manager.get_stream_buf_length("lalipop"));
//
//    add_data_in_buffer(buf, "aaaaI{gooddata}IaaI{aa");
//    manager.new_message("lalipop");
//    CHECK(manager.get_stream_buf_length("lalipop") == 4);
//
//    add_data_in_buffer(buf, "bbI{bbbI{dqI{gooddata}Ibbbb");
//    manager.new_message("lalipop");
//    CHECK(!manager.get_stream_buf_length("lalipop"));

}