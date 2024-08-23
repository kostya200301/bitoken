cmake_minimum_required(VERSION 3.10)
project(bitocen)


set(SOURCES
        CryptoHelper.cpp
        CryptoHelper.h
)

add_library(crypto STATIC ${SOURCES})


#target_link_libraries(crypto PUBLIC )
