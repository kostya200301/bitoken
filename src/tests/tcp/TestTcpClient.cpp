#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpClient.h"
#include "crypto/CryptoHelper.h"
#include <thread>
#include <spdlog/spdlog.h>
#include "model/Core.h"
using namespace std::chrono_literals;

std::string get_test_json(int i) {
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

TEST_CASE("Test tcp client", "[model][unit][coverage]") {

    model::Core core;

    core.configure(12446);

    auto client = core.get_tcp_manager_mes()->add_tcp_client("localhost", 12345, "inf" + std::to_string(123));
    auto client2 = core.get_tcp_manager_mes()->add_tcp_client("localhost", 12345, "inf" + std::to_string(124));
    std::this_thread::sleep_for(1s);
        for (int i = 0; i < 25000; i++) {
            std::string aaa = "alallI{I{{{III{{sqsqsII{\"type\":\"TestMessage\",\"Poni\":" + std::to_string(123) + "}Isqsqw}}}}I}I}I}sqsqw}I}IqwsqI{{{";
            client->send_message(aaa);
            client2->send_message(aaa);
        }

        std::this_thread::sleep_for(10s);

//    std::string server = "localhost";
//    short port = 12345;
//
//
//
//    boost::asio::io_context io_context;
//
//    tcp::TcpClient client(io_context, server, port);
//    client.start();
//
//    std::thread io_thread([&io_context]() {
//        io_context.run();
//    });
//
//    std::this_thread::sleep_for(1s);
//
//    std::string data = get_test_json(123);
//    std::string big_data = get_test_json(123);
//    big_data = big_data + big_data + big_data + big_data;
//    big_data = big_data;
//    std::string aaa = "alallI{I{{{III{{sqsqsII{\"type\":\"TestMessage\",\"Poni\":" + std::to_string(123) + "}Isqsqw}}}}I}I}I}sqsqw}I}IqwsqI{{{";
//    std::string big_aaa = aaa + aaa + aaa + aaa;
//    big_data = data + data + data + data + data + data + data + data + data + data;
//    for (int i = 0; i < 25000; i++) {
//
//        client.send_message(big_data);
//
//    }
//
//    io_thread.join();


}