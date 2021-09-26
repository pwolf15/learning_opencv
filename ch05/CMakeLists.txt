project(ch05)

add_executable(circle circle.cpp)
target_link_libraries(circle ${OpenCV_LIBS})
