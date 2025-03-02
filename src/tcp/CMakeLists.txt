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
        tcp_message_parts/TcpMessageSPart.cpp
)

# Добавляем исполняемый файл
add_library(tcp STATIC ${SOURCES})

target_compile_features(tcp PUBLIC cxx_std_17)
target_link_libraries(tcp PUBLIC Boost::system Boost::asio Boost::coroutine Boost::context OpenSSL::SSL OpenSSL::Crypto)

target_link_libraries(tcp PUBLIC model)