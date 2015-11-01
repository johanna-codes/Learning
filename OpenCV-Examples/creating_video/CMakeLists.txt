cmake_minimum_required(VERSION 2.8)
project(write-video)
find_package( OpenCV REQUIRED)
add_executable( writing.exe video-write.cpp)
target_link_libraries( writing.exe ${OpenCV_LIBS})

