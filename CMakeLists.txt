cmake_minimum_required(VERSION 3.6)
project(MatrixTemplate)

set(CMAKE_CXX_STANDARD 11)


add_subdirectory(testDirectory)

set(SOURCE_FILES main.cpp Matrix.h)
add_executable(MatrixTemplate ${SOURCE_FILES})

