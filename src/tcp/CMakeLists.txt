cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(SOURCES
        TcpServer.cpp
)

# Добавляем исполняемый файл
add_library(tcp STATIC ${SOURCES})

target_link_libraries(tcp PUBLIC Boost::system)
