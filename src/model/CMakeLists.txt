cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(SOURCES
        ConnectionsManager.cpp
        MessagesQueue.cpp
        Messages/TestMessage.cpp
        Messages/IMessage.cpp
        MessagesManager.cpp
        PoolManager.cpp
        Core.cpp
)

# Добавляем исполняемый файл
add_library(model STATIC ${SOURCES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(model PUBLIC json Boost::system Boost::asio TBB::tbb)