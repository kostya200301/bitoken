cmake_minimum_required(VERSION 3.10)
project(bitocen)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/simdjson)

include_directories(${CMAKE_SOURCE_DIR}/libs/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/simdjson/include)
include_directories(${CMAKE_SOURCE_DIR}/src)


add_subdirectory(src/json)
add_subdirectory(src/model)
add_subdirectory(src/tests)
