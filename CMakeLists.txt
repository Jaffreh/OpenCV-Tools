cmake_minimum_required(VERSION 3.1)

project(LearningCV)

find_package(OpenCV REQUIRED)

set(OpenCV_INCLUDE_DIRS '${OpenCV_DIR}/')
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main ${OpenCV_LIBS})
