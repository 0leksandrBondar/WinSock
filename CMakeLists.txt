cmake_minimum_required(VERSION 3.16..3.30)

project(WinSock)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Source)
add_subdirectory(Dependencies)
add_subdirectory(ClientExample)
add_subdirectory(ServerExample)

