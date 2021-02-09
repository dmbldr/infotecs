cmake_minimum_required(VERSION 3.8)
project(server)

set(SOURCES
        main.cpp
        network_connection_server.cpp)
set(HEADERS
        network_connection_server.h)

add_executable(client ${SOURCES} ${HEADERS})

set_target_properties(
        server PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)