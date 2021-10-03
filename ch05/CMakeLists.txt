project(ch05)

add_executable(circle circle.cpp)
target_link_libraries(circle ${OpenCV_LIBS})

add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${OpenCV_LIBS})

