cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(SOURCES
        IoContextManager.cpp
        CoreError.cpp
)

# Добавляем исполняемый файл
add_library(tools STATIC ${SOURCES})

target_link_libraries(tools PUBLIC Boost::system Boost::asio Boost::coroutine Boost::context)
