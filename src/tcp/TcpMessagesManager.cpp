//
// Created by Константин Беляков on 24.08.2024.
//

#include "TcpMessagesManager.h"

#include <utility>
#include <iostream>
#include <spdlog/spdlog.h>


namespace tcp {

    TcpMessagesManager::TcpMessagesManager(const model::MessagesQueuePtr& messages_queue) : messages_queue_(messages_queue) {
        tcp_client_ = std::make_shared<TcpClient>(io_context_client, "localhost", 12345);
        tcp_server_ = std::make_shared<TcpServer>(io_context_server, 12345);

        new_messages_slot = tcp_server_->on_new_message_slot([this](const std::string& con_id, const std::string& mes) {
            messages_queue_->enqueue(con_id, mes);
        });

    }

    TcpMessagesManager::~TcpMessagesManager() {
        spdlog::info("[TCP] TcpMessagesManager: start stopping");

        if (initial) {
            io_context_server.stop();
            io_thread_server->join();

            io_context_client.stop();
            io_thread_client->join();

            new_messages_slot->disconnect();
        }

        spdlog::info("[TCP] TcpMessagesManager: stop");
    }

    void TcpMessagesManager::init() {
        spdlog::info("[TCP] TcpMessagesManager: init");
        io_thread_client = std::make_unique<std::thread>([self = shared_from_this()]() {
            self->start_client();
        });

        io_thread_server = std::make_unique<std::thread>([self = shared_from_this()]() {
            self->start_server();
        });

        initial = true;
    }

    void TcpMessagesManager::start_client() {
        tcp_client_->start();
        io_context_client.run();
    }

    void TcpMessagesManager::start_server() {
        tcp_server_->start_accept();
        io_context_server.run();
    }


}



