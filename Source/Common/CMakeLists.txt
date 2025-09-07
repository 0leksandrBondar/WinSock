cmake_minimum_required(VERSION 3.16..3.30)

set(SOURCE
    wsadata.h
    wsadata.cpp
    socketaddress.h
    socketaddress.cpp
    )

add_library(Common ${SOURCE}
    socket.h socket.cpp
    message.h message.cpp)

target_link_libraries(Common PUBLIC
    ws2_32
)

target_include_directories(Common PUBLIC ../)
