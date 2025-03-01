#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include <tools/IoContextManager.h>

int N = 25000;
auto end = std::chrono::steady_clock::now();

void example_task(int id) {
    // Сложные вычисления с большими числами
    long long k = 1233 * 314124;
    long long k2 = 1236 * 314124;
    long long k3 = 1235 * 314124;

    // Добавление дополнительных сложных вычислений
    long long result = 0;
    for (int i = 0; i < 1000000; ++i) {
        result += (i * i * i) % 123456789;
    }

    // Несколько вложенных циклов для увеличения нагрузки
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            result += (i * j) % 987654321;
        }
    }

    // Дополнительные вычисления с плавающей точкой
    double d = 1.0;
    for (int i = 0; i < 100000; ++i) {
        d = d * 1.00001 + 0.0001;
    }

    // Просто для отслеживания результатов (можно убрать, если не нужно)
    if (id % 1000 == 0)
        spdlog::info("Task {} completed complex calculations on thread {}", id, std::hash<std::thread::id>()(std::this_thread::get_id()));

    if (id == N) {
        spdlog::info("Set time end");
        end = std::chrono::steady_clock::now();
    }
}


TEST_CASE("Test IoContextManager", "[tools][unit][coverage]") {

    spdlog::set_level(spdlog::level::trace);

    // 1 - 43sec
    // 25 - 8.1sec
    // 30 - 4.1sec
    // 35 - 4.1sec
    // 45 - 4.4sec
    // 50 - 4.2sec

    const std::size_t num_threads = 25; // Количество потоков
    IoContextManager io_manager(num_threads);

    io_manager.start();

    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i <= N; ++i) {
        boost::asio::post(io_manager.get_io_context(), [i]() { example_task(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    spdlog::info("The time: {} ms", elapsed_ms.count());

    io_manager.stop();
    io_manager.start();
    io_manager.stop();
    io_manager.stop();
    io_manager.stop();
    io_manager.start();
    io_manager.start();
    io_manager.start();
    io_manager.stop();
    io_manager.start();

    for (int i = 0; i <= N; ++i) {
        boost::asio::post(io_manager.get_io_context(), [i]() { example_task(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

}