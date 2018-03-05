cmake_minimum_required(VERSION 2.8)

project(libevent)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-ggdb3 -std=c++0x -Wall -Werror -Wno-deprecated")

# add subdirectory 01.asynchronous-io
add_subdirectory(01.asynchronous-io)
