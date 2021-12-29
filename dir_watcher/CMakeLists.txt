cmake_minimum_required(VERSION 3.16.3)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(DirectoryWatcher)

# add the executable
add_executable(main main.cpp)

target_include_directories(main PUBLIC ./)