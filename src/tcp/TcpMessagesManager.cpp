//
// Created by Константин Беляков on 24.08.2024.
//

#include "TcpMessagesManager.h"

#include <utility>
#include <iostream>
#include <spdlog/spdlog.h>


namespace tcp {

    TcpMessagesManager::TcpMessagesManager(const model::MessagesQueuePtr& messages_queue, size_t server_port, size_t threads_count) : messages_queue_(messages_queue) {
        spdlog::info("[TCP] TcpMessagesManager: create");

        buffers_pool_ = std::make_shared<BuffersPool>(threads_count);
        buffers_manager_ = std::make_shared<BuffersManager>(buffers_pool_, messages_queue_, threads_count);
        tcp_server_ = std::make_shared<TcpServer>(io_context_server_, server_port, buffers_manager_);
    }

    void TcpMessagesManager::stop() {
        spdlog::info("[TCP] TcpMessagesManager: start stopping. {} clients", io_thread_clients_.size());

        if (initial) {
            io_context_server_.stop();
            io_thread_server->join();

            io_context_client_.stop();

            for (auto it = io_thread_clients_.begin(); it != io_thread_clients_.end(); it++) {
                it->second->join();
                spdlog::info("[TCP] TcpMessagesManager: client {} stop", it->first);
            }
//            io_thread_client->join();
        }

        spdlog::info("[TCP] TcpMessagesManager: stop");
    }

    TcpMessagesManager::~TcpMessagesManager() {
        spdlog::info("[TCP] TcpMessagesManager: destroyed");
    }

    tcp::TcpClientPtr TcpMessagesManager::add_tcp_client(const std::string& host, int port, const std::string& data)  {
        std::string id = host + "::" + std::to_string(port) + "::" + data;
        spdlog::info("[TCP] TcpMessagesManager: add tcp client {}", id);
        auto tcp_client = std::make_shared<TcpClient>(io_context_client_, host, port);
        tcp_clients_[id] = tcp_client;
        io_thread_clients_[id] = std::make_unique<std::thread>([self = shared_from_this(), id]() {
            self->start_client(id);
        });
        return tcp_client;
    }

    void TcpMessagesManager::init() {
        spdlog::info("[TCP] TcpMessagesManager: init");

        io_thread_server = std::make_unique<std::thread>([self = shared_from_this()]() {
            self->start_server();
        });

        initial = true;
    }

    void TcpMessagesManager::start_client(const std::string& id) {
        spdlog::info("[TCP] TcpMessagesManager: start client {}", id);
        tcp_clients_[id]->start();
        if (!io_context_client_act) { // ERROR так нельяза. Надо обдумать как оперировать контекстом!!!!
            io_context_client_.run();
            io_context_client_act = true;
        }
    }


    void TcpMessagesManager::start_server() {
        tcp_server_->start_accept();
        io_context_server_.run();
    }


}



