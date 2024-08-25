#ifndef THREAD_POOL_MANAGER_H
#define THREAD_POOL_MANAGER_H

#include <thread>
#include <mutex>
#include <memory>
#include <queue>
#include <functional>
#include <condition_variable>
#include <vector>

namespace model {

    class ThreadPoolManager;
    using ThreadPoolManagerPtr = std::shared_ptr<ThreadPoolManager>;

    class ThreadPoolManager {
    public:
        ThreadPoolManager();
        ~ThreadPoolManager();
        template<class F>
        void add_task(F&& func);
        void wait_completion();
        void start_threads_pool(int num_workers);


    private:
        int num_workers;
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;
    };

    template<class F>
    void ThreadPoolManager::add_task(F&& func) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(func));
        }
        condition.notify_one();
    }
}

#endif
