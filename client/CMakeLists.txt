cmake_minimum_required(VERSION 3.8)
project(client)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(threadsafe_filework)
add_subdirectory(joining_thread)
add_subdirectory(main)