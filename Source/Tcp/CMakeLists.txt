cmake_minimum_required(VERSION 3.16..3.30)

set(SOURCE
    socket.h
    socket.cpp
    server.h
    server.cpp
    )

add_library(TCP ${SOURCE})

target_link_libraries(TCP PUBLIC
    Common
    spdlog
)

target_include_directories(TCP PUBLIC ./)
