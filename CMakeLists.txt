cmake_minimum_required(VERSION 3.5)

project(LocalBinaryPattern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(LocalBinaryPattern main.cpp RGB.h Image.h)

target_link_libraries(LocalBinaryPattern ${OpenCV_LIBS} )
