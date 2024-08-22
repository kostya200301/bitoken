cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

#find_package(PkgConfig REQUIRED)
#
#pkg_check_modules(RAPIDJSON REQUIRED rapidjson)
#
#if (NOT RAPIDJSON_FOUND)
#    message(FATAL_ERROR "RapidJSON not found!")
#endif()
#
#pkg_check_modules(SIMDJSON REQUIRED simdjson)
#
#if (NOT SIMDJSON_FOUND)
#    message(FATAL_ERROR "simdjson not found!")
#endif()


set(SOURCES
        JSONHelper.cpp
        JSONHelper.h
)

add_library(json SHARED ${SOURCES})

#message("lalal ${RAPIDJSON_INCLUDE_DIRS} I ${SIMDJSON_INCLUDE_DIRS}")

#target_include_directories(json PUBLIC ${RAPIDJSON_INCLUDE_DIRS} ${SIMDJSON_INCLUDE_DIRS})

#target_link_directories(json PUBLIC ${SIMDJSON_LIBRARY_DIRS})

target_link_libraries(json PUBLIC simdjson::simdjson)
