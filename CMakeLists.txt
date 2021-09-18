cmake_minimum_required(VERSION 3.21.1)

# This will be the name of the 
# executable.
# This is also the source of the 
# version information
project(poppler_build VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

# setting up subprojects
# src: https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic
add_subdirectory(wrapperLib)  

target_link_libraries(${PROJECT_NAME}
  wrapper)