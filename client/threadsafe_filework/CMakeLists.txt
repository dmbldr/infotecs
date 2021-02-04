cmake_minimum_required(VERSION 3.8)
project(threadsafe_filework)

add_library (threadsafe_filework STATIC  "threadsafe_filework.cpp")
set_target_properties(
        threadsafe_filework PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)