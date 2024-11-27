#include "catch2/catch.hpp"
#include "model/MessagesQueue.h"
#include <iostream>
#include <memory>
#include <thread>
#include "model/Messages/TestMessage.h"

using namespace std::chrono_literals;

TEST_CASE("Test messages queue", "[model][unit][coverage]") {
    spdlog::set_level(spdlog::level::trace);
    auto pool_manager_ = std::make_shared<model::ThreadPoolManager>();
    pool_manager_->start_threads_pool(5);
    model::MessagesQueuePtr queue = std::make_shared<model::MessagesQueue>(pool_manager_);

    std::string data = R"({
"type": "TestMessage",
"lala": 123,
"items": [
{
  "id": 1,
  "name": "Item1",
  "attributes": {
    "color": "red",
    "size": "M",
    "price": 19.99,
    "in_stock": true
  }
},
{
  "id": 2,
  "name": "Item2",
  "attributes": {
    "color": "blue",
    "size": "L",
    "price": 29.99,
    "in_stock": false
  }
}
],
"metadata": {
"created_at": "2024-08-26T12:34:56Z",
"updated_at": "2024-08-27T13:45:00Z",
"version": 2
},
"nested": {
"level1": {
  "level2": {
    "level3": {
      "description": "This is a deeply nested object",
      "values": [1, 2, 3, 4, 5]
    }
  }
}
},
"users": [
{
  "user_id": "abc123",
  "name": "John Doe",
  "roles": ["admin", "user"],
  "preferences": {
    "notifications": {
      "email": true,
      "sms": false
    },
    "theme": "dark"
  }
},
{
  "user_id": "def456",
  "name": "Jane Smith",
  "roles": ["user"],
  "preferences": {
    "notifications": {
      "email": false,
      "sms": true
    },
    "theme": "light"
  }
},    {
  "user_id": "def456",
  "name": "Jane Smith",
  "roles": ["user"],
  "preferences": {
    "notifications": {
      "email": false,
      "sms": true
    },
    "theme": "light"
  }
}
],
"log": [
{
  "event": "login",
  "timestamp": "2024-08-26T14:00:00Z",
  "details": "User logged in successfully"
},
{
  "event": "update",
  "timestamp": "2024-08-26T15:00:00Z",
  "details": "User updated profile"
}
]
})";
    int N = 500000;

    std::thread trx1([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    std::thread trx2([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    std::thread trx3([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    std::thread trx4([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    std::thread trx5([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    std::thread trx6([&]() {
        for (int i = 0; i < N; i++) {
            queue->enqueue("con1", data);
        }
    });

    auto start = std::chrono::steady_clock::now();

    int sz = queue->get_size_approx();
    while (sz != 6 * N) {
        spdlog::trace("Queue size: {}", sz);
        std::this_thread::sleep_for(666ms);
        sz = queue->get_size_approx();
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    spdlog::info("The time: {} ms", elapsed_ms.count());


    spdlog::trace("Queue size: {}", sz);
    CHECK(queue->get_size_approx() == 6 * N);

    trx1.join();
    trx2.join();
    trx3.join();
    trx4.join();
    trx5.join();
    trx6.join();


}