project(ch07)

add_executable(pca pca.cpp)
target_link_libraries(pca ${OpenCV_LIBS})

add_executable(rng rng.cpp)
target_link_libraries(rng ${OpenCV_LIBS})

add_executable(svd svd.cpp)
target_link_libraries(svd ${OpenCV_LIBS})