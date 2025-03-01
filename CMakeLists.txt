cmake_minimum_required(VERSION 3.10)

project(bitocen)

# add dop dirs
include_directories(${CMAKE_INCLUDE_PATH})
link_directories(${CMAKE_LIBRARY_PATH})

add_library(Cassandra INTERFACE)
find_library(CASSANDRA_LIBRARY NAMES cassandra PATHS ${CASSANDRA_LIB_DIR})

if(CASSANDRA_LIBRARY)
    message("Cassandra library found")
    target_link_libraries(Cassandra INTERFACE ${CASSANDRA_LIBRARY})
else()
    message(FATAL_ERROR "Cassandra library not found")
endif()


message(STATUS "C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

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
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/concurrentqueue)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/oneTBB)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/openfhe-development)



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
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/config/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/assert/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/throw_exception/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/system/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/uuid/include)
include_directories(${BOOST_INCLUDE_DIRS})

#boost signals
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/signals2/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/variant/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/type_index/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost/libs/parameter/include)


#concurrentqueue
include_directories(${CMAKE_SOURCE_DIR}/libs/concurrentqueue)



include_directories(${CMAKE_SOURCE_DIR}/libs/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/simdjson/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

#Spdlog
include_directories(${CMAKE_SOURCE_DIR}/libs/spdlog/include)

#oneTBB multiTHREAD
include_directories(${CMAKE_SOURCE_DIR}/libs/oneTBB/include)

#openFHE crypto
include_directories(${CMAKE_SOURCE_DIR}/libs/openfhe-development/src/pke/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/openfhe-development/src/core/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/openfhe-development/third-party)
include_directories(${CMAKE_SOURCE_DIR}/libs/openfhe-development/third-party/cereal/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/openfhe-development/src/binfhe/include)
# ???????
include_directories(${CMAKE_BINARY_DIR}/libs/openfhe-development/src/core)
# ?????

add_subdirectory(src/json)
add_subdirectory(src/tools)
add_subdirectory(src/model)
add_subdirectory(src/tcp)
add_subdirectory(src/crypto)
add_subdirectory(src/db)
add_subdirectory(src/tests)