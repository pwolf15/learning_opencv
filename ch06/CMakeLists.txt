project(ch06)

add_executable(shapes shapes.cpp)
target_link_libraries(shapes ${OpenCV_LIBS})
