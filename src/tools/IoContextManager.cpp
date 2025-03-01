//
// Created by Константин Беляков on 02.12.2024.
//

#include "IoContextManager.h"

IoContextManager::IoContextManager(std::size_t num_threads) : work_guard_(boost::asio::make_work_guard(io_context_)),
                                                                num_threads_(num_threads), status_(IoContextManagerStatus::Created) {
    spdlog::trace("[tools] Create IoContextManager with {} threads", num_threads);
}


void IoContextManager::start() {
    spdlog::trace("[tools] IoContextManager: Start IoContextManager with {} threads", num_threads_);

    const std::lock_guard<std::mutex> lock(mtx_);

    if (status_ == IoContextManagerStatus::Created) {
        status_ = IoContextManagerStatus::Running;
    } else if (status_ == IoContextManagerStatus::Stopped) {
        spdlog::trace("[tools] IoContextManager: Reset IoContextManager with {} threads", num_threads_);
        io_context_.reset();
        status_ = IoContextManagerStatus::Running;
    } else if (status_ == IoContextManagerStatus::Running) {
        spdlog::warn("[tools] IoContextManager: Try start running IoContextManager, ignore");
        return;
    }

    for (std::size_t i = 0; i < num_threads_; ++i) {
        threads_.emplace_back([this]() { io_context_.run(); });
    }
}


void IoContextManager::stop() {
    const std::lock_guard<std::mutex> lock(mtx_);
    if (status_ == IoContextManagerStatus::Stopped) {
        spdlog::warn("[tools] IoContextManager: Try stop stopped IoContextManager, ignore");
        return;
    } else if (status_ == IoContextManagerStatus::Running) {
        spdlog::trace("[tools] IoContextManager: stop");
        io_context_.stop();
        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        threads_.clear();
        status_ = IoContextManagerStatus::Stopped;
    }
}


boost::asio::io_context& IoContextManager::get_io_context() {
    return io_context_;
}

IoContextManager::~IoContextManager() {
    spdlog::trace("[tools] Destroy IoContextManager");
    stop();
}