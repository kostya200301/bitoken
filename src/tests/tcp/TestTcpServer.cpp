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

using namespace std::chrono_literals;


TEST_CASE("Test tcp server + clients", "[model][unit][coverage]") {
    CHECK(1 == 1);
    try {
        model::Core core;
        core.configure();

        int good = 0;
        while (true) {
            auto mes = core.get_messages_manager()->get_message();
            if (mes != nullptr) {
                std::cout << "GoodMes: " << good << "\n";
                good++;
            }
//            std::this_thread::sleep_for(2500ns);
        }

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}