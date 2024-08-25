#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpClient.h"
#include "crypto/CryptoHelper.h"
#include <thread>

using namespace std::chrono_literals;

TEST_CASE("Test tcp client", "[model][unit][coverage]") {
//    std::string server = "localhost";
//    short port = 12345;
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
//    for (int i = 0; i < 33333; i++) {
//        if (i % 3 == 0) {
//            client.send_message("IIDIAIWDIAWIDIAWDAWDIAWID123123IIIDAWd");
//        } else {
//            client.send_message("\"I{\"type\":\"TestMessage\",\"Poni\":\" + std::to_string(i) + \"}I\"");
//        }
//
//    }
//
//    io_thread.join();


        std::string server = "localhost";
        short port = 12345;

        std::vector<std::shared_ptr<tcp::TcpClient>> clients;
        std::vector<std::shared_ptr<boost::asio::io_context>> contexts;
        std::vector<std::shared_ptr<std::thread>> threadts;
        for (int i = 0; i < 250; i++) {
            std::this_thread::sleep_for(5ms);
            contexts.push_back(std::make_shared<boost::asio::io_context>());
            clients.push_back(std::make_shared<tcp::TcpClient>(*contexts[i], server, port));
            clients[i]->start();
            threadts.push_back(std::make_shared<std::thread>([&contexts, i]() {
                contexts[i]->run();
            }));
        }

        std::this_thread::sleep_for(5s);

        for (int i = 0; i < 33333; i++) {
            std::this_thread::sleep_for(100ms);
            for (auto client : clients) {
                if (i % 3 == 0) {
                    client->send_message("IIDIAIWDIAWIDIAWDAWDIAWID123123IIIDAWd");
                } else {
                    client->send_message("I{\"type\":\"TestMessage\",\"Poni\":" + std::to_string(i) + "}I");
                }
            }
        }


//    std::string server = "localhost";
//    short port = 12345;
//
//    std::vector<std::shared_ptr<tcp::TcpClient>> clients;
//    std::vector<std::shared_ptr<boost::asio::io_context>> contexts;
//    std::vector<std::shared_ptr<std::thread>> threadts;
//    for (int i = 0; i < 1; i++) {
//        contexts.push_back(std::make_shared<boost::asio::io_context>());
//        clients.push_back(std::make_shared<tcp::TcpClient>(*contexts[i], server, port));
//        clients[i]->start();
//        threadts.push_back(std::make_shared<std::thread>([&contexts, i]() {
//            contexts[i]->run();
//        }));
//    }
//
//    std::this_thread::sleep_for(3s);
//
//    for (int i = 0; i < 3333; i++) {
//        for (auto client : clients) {
//            client->send_message("Message" + std::to_string(i));
//        }
//    }


}