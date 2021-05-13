cmake_minimum_required(VERSION 3.19)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR /home/blackstone/Downloads/opencv-4.5.1/build)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(NeuralNetwork main.cpp Network.cpp Network.h Layer.cpp Layer.h Output.cpp Output.h)
target_link_libraries(NeuralNetwork ${OpenCV_LIBS} )