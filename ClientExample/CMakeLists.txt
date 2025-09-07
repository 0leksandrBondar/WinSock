cmake_minimum_required(VERSION 3.16..3.30)

project(ClientExample)

set(SOURCE main.cpp)

add_executable(ClientExample ${SOURCE})

target_link_libraries(ClientExample PUBLIC
        Common
        spdlog
        TCP
)
