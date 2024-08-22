cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/simdjson)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs/rapidjson/include)

message("${CMAKE_SOURCE_DIR}")
message("${CMAKE_SOURCE_DIR}/libs/rapidjson/include")

add_subdirectory(src/json)
add_subdirectory(src/model)
add_subdirectory(src/tests)
