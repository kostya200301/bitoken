cmake_minimum_required(VERSION 3.10)
project(bitocen)


set(SOURCES
        ScyllaDB/DBConnection.cpp
        ScyllaDB/DBQueryResult.cpp
        ScyllaDB/DBQueryIterator.cpp
        ScyllaDB/DBRow.cpp
        ScyllaDB/DBValue.cpp
        ScyllaDB/Feature.cpp
        DBQuery.cpp
)

add_library(db STATIC ${SOURCES})


target_link_libraries (db PUBLIC Cassandra)

