project(wrapper)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_library(${PROJECT_NAME} wrapper.cpp)

# define an alias to avoid any potential issues
# with target_link_libraries
add_library(lib::poppler_wrapper ALIAS ${PROJECT_NAME})

set(BUILD_SHARED_LIBS YES)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION 0.0.1
    SOVERSION 0
)

# source: https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
find_package(PkgConfig REQUIRED)

pkg_check_modules(POPPLER_CPP REQUIRED poppler-cpp)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${POPPLER_CPP_STATIC_LIBRARIES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    # Include output from pkg_config
    PUBLIC ${POPPLER_CPP_INCLUDE_DIRS}
    # Need to add this to use 
    # generated export headers
    ${PROJECT_BINARY_DIR}
)

target_compile_options(${PROJECT_NAME} 
    PUBLIC ${POPPLER_CPP_CFLAGS_OTHER})

# add these lines to allow exporting symbols
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

install(FILES include/wrapper/wrapper.h  DESTINATION include)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h"  DESTINATION include)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)