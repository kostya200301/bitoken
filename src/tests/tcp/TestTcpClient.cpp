#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpClient.h"
#include "crypto/CryptoHelper.h"
#include <thread>

using namespace std::chrono_literals;

TEST_CASE("Test tcp client", "[model][unit][coverage]") {
    std::string server = "localhost";
    short port = 12345;

    boost::asio::io_context io_context;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tlsv12_client);

    auto cert = crypto::CryptoHelper::getCertCrt();
    ssl_context.add_certificate_authority(boost::asio::buffer(cert.data(), cert.size()));

    tcp::TcpClient client(io_context, ssl_context, server, port);
    client.start();

//    io_context.run();
    std::thread io_thread([&io_context]() {
        io_context.run();
    });


    for (int i = 0; i < 333; i++) {
        std::this_thread::sleep_for(666ms);
        client.send_message("Message" + std::to_string(i));
    }

    io_thread.join();
}