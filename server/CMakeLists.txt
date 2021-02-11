cmake_minimum_required(VERSION 3.8)
project(server)

set(SOURCES
        main.cpp
        network_connection_server.cpp
        server_processor.cpp)
set(HEADERS
        network_connection_server.h
        server_processor.h)

add_executable(server ${SOURCES} ${HEADERS})

set_target_properties(
        server PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)