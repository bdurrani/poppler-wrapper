cmake_minimum_required(VERSION 3.16)

# You can also use ExternalProject_Add()
# An example of this: https://mirkokiefer.com/cmake-by-example-f95eb47d45b1

# include(FetchContent)

# FetchContent_Declare(
#   poppler_repo
#   GIT_REPOSITORY git@gitlab.freedesktop.org:poppler/poppler.git
#   GIT_SHALLOW TRUE
#   GIT_TAG tags/poppler-21.09.0
#   )

# FetchContent_MakeAvailable(poppler_repo)

project(topProject)
set(CMAKE_CXX_STANDARD 14)

enable_testing()

# required to perform memory tests
include(CTest)

# enable all compiler warning messages across
# all projects
# CppCon 2017: Mathieu Ropert “Using Modern CMake Patterns to Enforce a Good Modular Design”
# https://www.youtube.com/watch?v=eC9-iRN2b04&t=2802s
if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()


# setting up subprojects
# src: https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic
add_subdirectory(wrapperLib)  
add_subdirectory(tests)  
