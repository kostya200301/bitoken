cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        JSONHelper.cpp
        JSONHelper.h
)

add_library(json SHARED ${SOURCES})

#message("lalal ${RAPIDJSON_INCLUDE_DIRS} I ${SIMDJSON_INCLUDE_DIRS}")

#target_include_directories(json PUBLIC ${RAPIDJSON_INCLUDE_DIRS} ${SIMDJSON_INCLUDE_DIRS})

#target_link_directories(json PUBLIC ${SIMDJSON_LIBRARY_DIRS})

target_link_libraries(json PUBLIC simdjson::simdjson)
