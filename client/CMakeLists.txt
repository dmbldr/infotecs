cmake_minimum_required(VERSION 3.8)
project(client)
SET(CMAKE_CXX_FLAGS -pthread)

set(SOURCES
        main.cpp
        threadsafe_filework.cpp
        processor.cpp
        network_connection.cpp)
set(HEADERS
        threadsafe_filework.h
        processor.h
        network_connection.h)

add_executable(client ${SOURCES} ${HEADERS})

set_target_properties(
        client PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)