cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/simdjson)
include_directories(${CMAKE_SOURCE_DIR}/libs/rapidjson/include)

add_subdirectory(src/json)
add_subdirectory(src/model)
add_subdirectory(src/tests)
