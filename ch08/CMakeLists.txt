cmake_minimum_required(VERSION 3.0)

project(ch08)

find_package(OpenCV)

add_executable(canny canny.cpp)
target_link_libraries(canny ${OpenCV_LIBS})

add_executable(show_pixel show_pixel.cpp)
target_link_libraries(show_pixel ${OpenCV_LIBS})

add_executable(color_histogram color_histogram.cpp)
target_link_libraries(color_histogram ${OpenCV_LIBS})

