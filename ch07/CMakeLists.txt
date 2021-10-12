project(ch07)

add_executable(rng rng.cpp)
target_link_libraries(rng ${OpenCV_LIBS})