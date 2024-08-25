#include "catch2/catch.hpp"
#include "model/MessagesQueue.h"
#include <iostream>
#include <memory>
#include <thread>
#include "model/Messages/TestMessage.h"

using namespace std::chrono_literals;

TEST_CASE("Test messages queue", "[model][unit][coverage]") {
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

    int N = 100000;

    for (int i = 0; i < N; i++) {
        queue->enqueue("con1", data);
    }

    std::this_thread::sleep_for(100ms);

    for (int i = 0; i < N; i++) {
        auto mes = queue->dequeue();
        CHECK(mes != nullptr);
        int val = mes->get_json_parser()->get_json()["lala"].get_int64();
        CHECK(val == 123);
    }
    auto mes = queue->dequeue();
    CHECK(mes == nullptr);

}