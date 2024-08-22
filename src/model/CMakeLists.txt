cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        ConnectionsManager.cpp
)

# Добавляем исполняемый файл
add_library(model SHARED ${SOURCES})

# Указываем библиотеки, которые нужно подключить
#target_link_libraries(db json)