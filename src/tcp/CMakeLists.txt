cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(SOURCES
        TcpServer.cpp
        TcpClient.cpp
        TcpMessagesManager.cpp
        BuffersPool.cpp
        Buffer.cpp
        BufferWorm.cpp
        BuffersManager.cpp
)

# Добавляем исполняемый файл
add_library(tcp STATIC ${SOURCES})

target_link_libraries(tcp PUBLIC Boost::system Boost::asio OpenSSL::SSL OpenSSL::Crypto)

target_link_libraries(tcp PUBLIC model)