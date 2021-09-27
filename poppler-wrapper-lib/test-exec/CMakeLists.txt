project(test_exec_build VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(exeName test-exec)

add_executable(${exeName}
  main.cpp
)

target_link_libraries(${exeName}
  lib::poppler_wrapper
)

add_test(NAME Extracts-Text-WithActualText 
  COMMAND ${exeName} 
  WithActualText.pdf
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_test(NAME Extracts-Text-rbc 
  COMMAND ${exeName} 
  rbc.pdf
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})