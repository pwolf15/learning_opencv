cmake_minimum_required(VERSION 3.0)

project(ch08)

find_package(OpenCV)

add_executable(canny canny.cpp)
target_link_libraries(canny ${OpenCV_LIBS})
