project(ch06)

add_executable(shapes shapes.cpp)
target_link_libraries(shapes ${OpenCV_LIBS})

add_executable(text text.cpp)
target_link_libraries(text ${OpenCV_LIBS})

add_executable(frame_counter frame_counter.cpp)
target_link_libraries(frame_counter ${OpenCV_LIBS})
