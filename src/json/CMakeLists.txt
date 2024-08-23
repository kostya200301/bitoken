cmake_minimum_required(VERSION 3.10)
project(bitocen)


set(SOURCES
        JSONHelper.cpp
        JSONHelper.h
        ../crypto/CryptoHelper.cpp
        ../crypto/CryptoHelper.h
)

add_library(json STATIC ${SOURCES})


target_link_libraries(json PUBLIC simdjson::simdjson)
