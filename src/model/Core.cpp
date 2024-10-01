//
// Created by Константин Беляков on 24.08.2024.
//

#include "Core.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

#include "tcp/TcpClient.h"
#include "tcp/TcpServer.h"


namespace model {

    Core::Core() {
        spdlog::info("[MODEL] Core: create");
    }

    void Core::configure(int server_port) { // WARN нужен кор конфигуратор
        spdlog::info("[MODEL] Core: configure");


        spdlog::set_level(spdlog::level::info);
//        spdlog::set_level(spdlog::level::trace);
//        spdlog::set_level(spdlog::level::off);

        pool_manager_ = std::make_shared<model::ThreadPoolManager>();
        pool_manager_->start_threads_pool(5);
        messages_queue_ = std::make_shared<model::MessagesQueue>(pool_manager_);
        tcp_manager_mes_ = std::make_shared<tcp::TcpMessagesManager>(messages_queue_, server_port, 5);
        tcp_manager_mes_->init();
        messages_manager_ = std::make_shared<model::MessagesManager>(tcp_manager_mes_);

    }


    Core::~Core() {
        tcp_manager_mes_->stop();
        spdlog::info("[MODEL] Core: destroy");

    }


}
