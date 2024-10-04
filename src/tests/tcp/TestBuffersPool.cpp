#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpClient.h"
#include "crypto/CryptoHelper.h"
#include <thread>
#include <spdlog/spdlog.h>
#include "tcp/BuffersPool.h"
using namespace std::chrono_literals;

TEST_CASE("Test buffers pool", "[model][unit][coverage]") {
    int N = 25;
    auto pool = std::make_shared<tcp::BuffersPool>(N);
    std::vector<tcp::BufferPtr> buffers;

    for (int i = 0; i < N; i++) {
        auto p = pool->get_buffer();
        CHECK(p != nullptr);
        buffers.push_back(p);
    }

//    CHECK(pool->get_busy_buffers_count() == N);
    CHECK(pool->get_free_buffers_count() == 0);

    for (int i = 0; i < N; i++) {
        buffers[i]->finish_work();
    }
    buffers.clear();

//    CHECK(pool->get_busy_buffers_count() == 0);
    CHECK(pool->get_free_buffers_count() == 0);

    for (int i = 0; i < N; i++) {
        auto p = pool->get_buffer();
        CHECK(p != nullptr);
        buffers.push_back(p);
    }

//    CHECK(pool->get_busy_buffers_count() == N);
    CHECK(pool->get_free_buffers_count() == 0);


}