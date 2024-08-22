cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES
        JSONHelper.cpp
        JSONHelper.h
)

add_library(json STATIC ${SOURCES})


target_link_libraries(json PUBLIC simdjson::simdjson)
