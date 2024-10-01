#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/BuffersManager.h"
#include <thread>
#include <spdlog/spdlog.h>
using namespace std::chrono_literals;


void write_to_buffer(std::shared_ptr<boost::asio::streambuf> buffer, const std::string& data) {
    std::ostream os(buffer.get());
    os << data;
}

TEST_CASE("Test tcp client", "[model][unit][coverage]") {
    spdlog::set_level(spdlog::level::trace);

    auto thread_pool = std::make_shared<model::ThreadPoolManager>();

    auto mes_queue = std::make_shared<model::MessagesQueue>(thread_pool);

    auto buf_pool = std::make_shared<tcp::BuffersPool>(5);
    auto manager = std::make_shared<tcp::BuffersManager>(buf_pool, mes_queue);
    manager->add_new_client("lalipop");

    auto buf1 = manager->get_buffer();
    write_to_buffer(buf1->get_boost_buffer(), "DadqDdI{adqDdQDI{\"type\":\"TestMessage");
    manager->add_new_buffer("lalipop", buf1);

    auto buf2 = manager->get_buffer();
    write_to_buffer(buf2->get_boost_buffer(), "\",\"Poni\":" + std::to_string(121));
    manager->add_new_buffer("lalipop", buf2);


    auto buf3 = manager->get_buffer();
    write_to_buffer(buf3->get_boost_buffer(), ",\"Petya\":" + std::to_string(312) + "}IACASCACAC}IAXAWXAI{\"lal");
    manager->add_new_buffer("lalipop", buf3);

    for (int i = 0; i < 50; i++) {
        auto buf = manager->get_buffer();
        write_to_buffer(buf->get_boost_buffer(), "I{\"type\":\"TestMessage\",\"Poni\":" + std::to_string(121 + i) + "}I");
        manager->add_new_buffer("lalipop", buf);
    }

    

}