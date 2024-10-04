#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpServer.h"
#include "tcp/TcpClient.h"
#include "tcp/TcpMessagesManager.h"
#include "model/MessagesManager.h"
#include "model/MessagesQueue.h"
#include "crypto/CryptoHelper.h"
#include "model/Core.h"
#include <thread>
#include "tests/TestUtils.h"

using namespace std::chrono_literals;


std::string get_test_json_(int i) {
    std::string big_data = R"(I{I{I{SWSWQSQSIIII{QWSI{I{
  "type": "TestMessage",
  "lala": 000000,
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
}IdqdqdqdI}I}I}I{I{I{I{)";
    big_data[67] = std::to_string(i % 10)[0];
    big_data[66] = std::to_string(i / 10 % 10)[0];
    big_data[65] = std::to_string(i / 100 % 10)[0];
    big_data[64] = std::to_string(i / 1000 % 10)[0];
    big_data[63] = std::to_string(i / 10000 % 10)[0];
    big_data[62] = '1';
    return big_data;
}

TEST_CASE("Test tcp server + clients", "[model][unit][coverage]") {
    CHECK(1 == 1);
    try {
        model::Core core;
        core.configure(12345);

        int NUM_MES = 50000;
        int NUM_SENDERS = 5;
        int SLEEP_BET_MES_MS = 0;

        std::vector<std::shared_ptr<model::Core>> senders;
        std::vector<std::thread> threads;
        for (int i = 0; i < NUM_SENDERS; i++) {
            auto new_core_sender = std::make_shared<model::Core>();
            senders.push_back(new_core_sender);
            senders[i]->configure(12346 + i);
            senders[i]->get_tcp_manager_mes()->add_tcp_client("localhost", 12345, "inf" + std::to_string(i));
        }

        auto data = get_test_json_(1233) + get_test_json_(1234) + get_test_json_(1235) + get_test_json_(1236) + get_test_json_(1237);
        std::this_thread::sleep_for(1s);
        std::vector<std::thread> threads2;
        for (int h = 0; h < senders.size(); h++) {
            threads2.emplace_back(std::thread([&, h] () {
                    for (int k = 0; k < NUM_MES; k++) {
                        senders[h]->get_tcp_manager_mes()->get_tcp_client("localhost::12345::inf" + std::to_string(h))->send_message(data);
                        SLEEP_MS(SLEEP_BET_MES_MS);
//                        SLEEP_BET_MES_MS++;
                    }
            }));
        }

        while (core.get_messages_queue()->get_size_approx() != NUM_MES * 5 * NUM_SENDERS) {
            spdlog::info("Queue size: {}", core.get_messages_queue()->get_size_approx());
            SLEEP_S(1);
        }
        spdlog::info("Queue size: {}", core.get_messages_queue()->get_size_approx());

        SLEEP_S(1);

        CHECK(core.get_messages_queue()->get_size_approx() == NUM_MES * 5 * NUM_SENDERS);

        for (int i = 0; i < threads.size(); i++) {
            threads[i].join();
        }

        for (int i = 0; i < threads2.size(); i++) {
            threads2[i].join();
        }



    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}