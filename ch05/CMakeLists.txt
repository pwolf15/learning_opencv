project(ch05)

add_executable(circle circle.cpp)
target_link_libraries(circle ${OpenCV_LIBS})

add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${OpenCV_LIBS})

add_executable(rectangle_ptr rectangle_ptr.cpp)
target_link_libraries(rectangle_ptr ${OpenCV_LIBS})

add_executable(pyramid pyramid.cpp)
target_link_libraries(pyramid ${OpenCV_LIBS})

add_executable(inverted_headers inverted_headers.cpp)
target_link_libraries(inverted_headers ${OpenCV_LIBS})

add_executable(compare compare.cpp)
target_link_libraries(compare ${OpenCV_LIBS})
