#include "PoolManager.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace model {

    ThreadPoolManager::ThreadPoolManager() {}

    void ThreadPoolManager::wait_completion() {
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

    void ThreadPoolManager::start_threads_pool(int num_workers) {
        num_workers = num_workers;
        stop = false;
        for (int i = 0; i < num_workers; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ThreadPoolManager::~ThreadPoolManager() {
        spdlog::info("[MODEL] ThreadPoolManager: start stopping thread pool manager");
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        wait_completion();
        spdlog::info("[MODEL] ThreadPoolManager: stop thread pool manager");
    }

}