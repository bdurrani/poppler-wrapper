project(test_exec_build VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(exeName test-exec)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${exeName}
  wrapper_tests.cpp
  helpers.h
  helpers.cpp
)

target_link_libraries(${exeName}
  lib::poppler_wrapper
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${exeName}
   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)