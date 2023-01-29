cmake_minimum_required(VERSION 3.0)

project(ch16)

find_package(OpenCV)

add_executable(optical_flow optical_flow.cpp)
target_link_libraries(optical_flow ${OpenCV_LIBS})
