cmake_minimum_required(VERSION 3.21.1)

# This will be the name of the 
# executable.
# This is also the source of the 
# version information
project(poppler_build VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)
