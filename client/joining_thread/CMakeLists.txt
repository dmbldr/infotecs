cmake_minimum_required(VERSION 3.8)
project(joining_thread)

add_library (joining_thread STATIC  "joining_thread.cpp")
set_target_properties(
        joining_thread PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)