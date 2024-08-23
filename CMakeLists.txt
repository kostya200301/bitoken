cmake_minimum_required(VERSION 3.10)

project(bitocen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS NO)

if(APPLE)
    message(STATUS "Building on macOS")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/simdjson)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/boost)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/spdlog)



find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Boost asio
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/align/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/mpl/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/asio/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/smart_ptr/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/static_assert/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/numeric/conversion/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/preprocessor/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/type_traits/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/core/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/utility/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/date_time/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/process/include)
include_directories(${BOOST_INCLUDE_DIRS})


include_directories(${CMAKE_SOURCE_DIR}/libs/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/simdjson/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

#Spdlog
include_directories(${CMAKE_SOURCE_DIR}/libs/spdlog/include)


add_subdirectory(src/json)
add_subdirectory(src/model)
add_subdirectory(src/tcp)
add_subdirectory(src/tests)