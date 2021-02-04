cmake_minimum_required(VERSION 3.8)
project(main)

add_executable(main "main.cpp")

include_directories("../joining_thread")
include_directories("../threadsafe_filework")

target_link_libraries(main joining_thread)
target_link_libraries(main threadsafe_fileowrk)