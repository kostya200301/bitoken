//
// Created by Константин Беляков on 02.12.2024.
//

#ifndef BITOCEN_IOCONTEXTMANAGER_H
#define BITOCEN_IOCONTEXTMANAGER_H


#include <boost/asio.hpp>
#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <spdlog/spdlog.h>
#include <mutex>

enum class IoContextManagerStatus {
    Default,
    Created,
    Running,
    Stopped,
};

class IoContextManager;
using IoContextManagerPtr = std::shared_ptr<IoContextManager>;

class IoContextManager {
public:
    explicit IoContextManager(std::size_t num_threads);

    ~IoContextManager();

    // Запускаем N потоков
    void start();

    // Останавливаем работу
    void stop();

    // Получаем io_context для работы
    boost::asio::io_context& get_io_context();

private:
    IoContextManagerStatus status_;

    std::mutex mtx_;
    boost::asio::io_context io_context_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard_;
    std::vector<std::thread> threads_;
    std::size_t num_threads_;
};



#endif //BITOCEN_IOCONTEXTMANAGER_H
