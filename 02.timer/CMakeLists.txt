cmake_minimum_required(VERSION 2.8)

add_executable(timer timer.cpp)
target_link_libraries(timer event)
