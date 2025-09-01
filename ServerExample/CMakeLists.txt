cmake_minimum_required(VERSION 3.16..3.30)

project(ServerExample)

set(SOURCE main.cpp)

add_executable(ServerExample ${SOURCE})

target_link_libraries(ServerExample PUBLIC
        spdlog
        Common
        TCP
)
