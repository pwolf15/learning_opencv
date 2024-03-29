cmake_minimum_required(VERSION 3.0)

project(CVExamples)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world ${OpenCV_LIBS})

add_executable(display_video display_video.cpp)
target_link_libraries(display_video ${OpenCV_LIBS})

add_executable(video_interactive video_interactive.cpp )
target_link_libraries(video_interactive ${OpenCV_LIBS})

add_executable(video_smoothing video_smoothing.cpp )
target_link_libraries(video_smoothing ${OpenCV_LIBS})

add_executable(image_transform image_transform.cpp )
target_link_libraries(image_transform ${OpenCV_LIBS})

add_executable(canny canny.cpp )
target_link_libraries(canny ${OpenCV_LIBS})

add_executable(pixels pixels.cpp )
target_link_libraries(pixels ${OpenCV_LIBS})

add_executable(video_capture video_capture.cpp )
target_link_libraries(video_capture ${OpenCV_LIBS})

add_executable(log_polar log_polar.cpp )
target_link_libraries(log_polar ${OpenCV_LIBS})

add_executable(downsample_video downsample_video.cpp )
target_link_libraries(downsample_video ${OpenCV_LIBS})

add_executable(downsampling_interactive downsampling_interactive.cpp )
target_link_libraries(downsampling_interactive ${OpenCV_LIBS})

add_executable(types types.cpp)
target_link_libraries(types ${OpenCV_LIBS})

add_executable(mat_examples mat_examples.cpp)
target_link_libraries(mat_examples ${OpenCV_LIBS})

add_executable(mat_sum mat_sum.cpp)
target_link_libraries(mat_sum ${OpenCV_LIBS})

add_executable(multi_mat_sum multi_mat_sum.cpp)
target_link_libraries(multi_mat_sum ${OpenCV_LIBS})

add_executable(sparse_mat sparse_mat.cpp)
target_link_libraries(sparse_mat ${OpenCV_LIBS})

add_executable(typewriter typewriter.cpp)
target_link_libraries(typewriter ${OpenCV_LIBS})

add_executable(integral_images integral_images.cpp)
target_link_libraries(integral_images ${OpenCV_LIBS})

add_executable(alpha_blending alpha_blending.cpp)
target_link_libraries(alpha_blending ${OpenCV_LIBS})

add_subdirectory(ch05)
add_subdirectory(ch06)
add_subdirectory(ch07)