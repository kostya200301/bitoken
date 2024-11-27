#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/BuffersManager.h"
#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>
#include "tests/TestUtils.h"
using namespace std::chrono_literals;


void write_to_buffer(std::shared_ptr<boost::asio::streambuf> buffer, const std::string& data) {
    std::ostream os(buffer.get());
    os << data;
}

TEST_CASE("Test tcp client", "[model][unit][coverage]") {
    spdlog::set_level(spdlog::level::trace);
//    spdlog::set_level(spdlog::level::off);

    size_t COUNT = 1000000;

    auto thread_pool = std::make_shared<model::ThreadPoolManager>();

    auto mes_queue = std::make_shared<model::MessagesQueue>(thread_pool);

    auto buf_pool = std::make_shared<tcp::BuffersPool>(5);
    auto manager = std::make_shared<tcp::BuffersManager>(buf_pool, mes_queue, 6);
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

    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < COUNT; i++) {
        auto buf = manager->get_buffer();
        write_to_buffer(buf->get_boost_buffer(), "I{\"type\":\"TestMessage\",\"Poni\":" + std::to_string(121 + i) + "}I");
        manager->add_new_buffer("lalipop", buf);
    }

    while (mes_queue->get_size_approx() != 0) {
        auto mes = mes_queue->dequeue();
        auto result = mes->get_json_parser()->get_json().get_string();
    }

//    WAIT_CONDITION_S(mes_queue->get_size_approx() == COUNT + 1, 100);
    auto end = std::chrono::steady_clock::now();

//    SLEEP_S(3);
//    CHECK(mes_queue->get_size_approx() == COUNT + 1);



    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    spdlog::info("The time: {} ms", elapsed_ms.count());
//    std::cout << elapsed_ms.count() << "\n";



}