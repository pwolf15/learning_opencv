cmake_minimum_required(VERSION 3.0)

project(CVExamples)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world ${OpenCV_LIBS})

add_executable(display_video display_video.cpp)
target_link_libraries(display_video ${OpenCV_LIBS})