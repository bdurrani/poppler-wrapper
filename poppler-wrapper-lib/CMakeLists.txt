cmake_minimum_required(VERSION 3.16)


project(topProject)
enable_testing()
# enable all compiler warning messages across
# all projects
# CppCon 2017: Mathieu Ropert “Using Modern CMake Patterns to Enforce a Good Modular Design”
# https://www.youtube.com/watch?v=eC9-iRN2b04&t=2802s
if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party)
# setting up subprojects
# src: https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic
add_subdirectory(wrapperLib)  
add_subdirectory(test-exec)  
