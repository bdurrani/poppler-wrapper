project(test_exec_build VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(exeName test-exec)
add_executable(${exeName}
  main.cpp
)

target_link_libraries(${exeName}
  wrapper
)
