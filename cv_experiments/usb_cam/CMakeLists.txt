cmake_minimum_required(VERSION 3.0)

project(UsbCam)

find_package(OpenCV)

add_executable(UsbCam usb_cam.cpp)

target_link_libraries(UsbCam ${OpenCV_LIBS})

add_executable(canny canny.cpp)

target_link_libraries(canny ${OpenCV_LIBS})
