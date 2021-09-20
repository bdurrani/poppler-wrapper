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
enable_testing()

# setting up subprojects
# src: https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic
add_subdirectory(wrapperLib)  
add_subdirectory(test-exec)  
