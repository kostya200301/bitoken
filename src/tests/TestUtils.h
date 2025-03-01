#pragma once

#include <catch2/catch.hpp>
#include <chrono>
#include <thread>

void sleep_ms(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void sleep_ns(int nanoseconds) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
}

#define REQUIRE_WAIT(action, event)                                                                                    \
    {                                                                                                                  \
        auto f = event;                                                                                                \
        REQUIRE_NOTHROW(action);                                                                                       \
        REQUIRE_NOTHROW(f->wait());                                                                                    \
    };

#define REQUIRE_WAIT_S(action, event, timeout_sec)                                                                     \
    {                                                                                                                  \
        auto f = event;                                                                                                \
        REQUIRE_NOTHROW(action);                                                                                       \
        REQUIRE_NOTHROW(f->wait(timeout_sec));                                                                         \
    };

#define ASYNC_BEGIN

#define ASYNC_END

#define ASYNC_END_TIMEOUT(timeout_sec)

#define WAIT_CONDITION(PRED)                                                                                           \
    APP_TRACE << "WAIT_CONDITION(" #PRED ")";                                                                          \
    while (![&] { return PRED; }())                                                                                    \
        sleep_ms(100);

static constexpr int DEFAULT_TIMEOUT{20};

#define SLEEP_UNTIL_MS(PRED, TIMEOUT_MS)                                                                               \
    APP_TRACE << "SLEEP_UNTIL_MS(" #PRED ")";                                                                          \
    for (int timeout = TIMEOUT_MS; ![&] { return PRED; }() && timeout > 0; timeout -= 100) {                           \
        sleep_ms(100);                                                                                                 \
    };

#define WAIT_CONDITION_MS(PRED, TIMEOUT_MS)                                                                            \
//    APP_TRACE << "WAIT_CONDITION_MS(" #PRED ")";                                                                       \
    for (int timeout = TIMEOUT_MS; ![&] { return PRED; }() && timeout > 0; timeout -= 100) {                           \
        sleep_ms(100);                                                                                                 \
    };                                                                                                                 \
    CHECK(PRED);

#define WAIT_CONDITION_S(PRED, TIMEOUT_S) WAIT_CONDITION_MS(PRED, TIMEOUT_S * 1000);
#define SLEEP_UNTIL_S(PRED, TIMEOUT_S) SLEEP_UNTIL_MS(PRED, TIMEOUT_S * 1000);

#define WAIT_FUTURE(future)                                                                                            \
    APP_TRACE << "WAIT_FUTURE(" #future ")";                                                                           \
    future->wait();

#define WAIT_FUTURE_DATA(type, var, future)                                                                            \
    APP_TRACE << "WAIT_FUTURE_DATA(" #type ", " #var ", " #future ")";                                                 \
    type var = future->wait_result_data();

#define SLEEP_NS(NS) sleep_ns(NS);
#define SLEEP_MS(MS) sleep_ms(MS);
#define SLEEP_S(S) sleep_ms(S * 1000);

#define REQUIRE_NOTHROW_RETURN(EXPR)                                                                                   \
    [&] {                                                                                                              \
        std::decay_t<decltype(EXPR)> val;                                                                              \
        REQUIRE_NOTHROW([&] { val = EXPR; }());                                                                        \
        return val;                                                                                                    \
    }()
#define CHECK_NOTHROW_RETURN(EXPR)                                                                                     \
    [&] {                                                                                                              \
        std::decay_t<decltype(EXPR)> val;                                                                              \
        CHECK_NOTHROW([&] { val = EXPR; }());                                                                          \
        return val;                                                                                                    \
    }()

template<typename C, typename T>
int count(C const& collection, T const& item) {
    int n = 0;
    for (auto const& i : collection) {
        if (i == item)
            ++n;
    }
    return n;
}

template<typename C>
C sorted(C collection) {
    std::sort(std::begin(collection), std::end(collection));
    return std::move(collection);
}

std::string& get_test_data();
