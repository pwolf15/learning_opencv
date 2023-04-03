cmake_minimum_required(VERSION 3.0)

project(ch17)

find_package(OpenCV)

add_executable(camshiftdemo camshiftdemo.cpp)
target_link_libraries(camshiftdemo ${OpenCV_LIBS})

add_executable(kcf kcf.cpp)
target_link_libraries(kcf ${OpenCV_LIBS})
