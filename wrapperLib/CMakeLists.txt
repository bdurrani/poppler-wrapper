project(wrapper)

add_library(${PROJECT_NAME} wrapper.cpp)

set(BUILD_SHARED_LIBS YES)

# add these lines
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

# source: https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
find_package(PkgConfig REQUIRED)

pkg_check_modules(POPPLER_CPP REQUIRED poppler-cpp)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${POPPLER_CPP_STATIC_LIBRARIES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${POPPLER_CPP_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
)

target_compile_options(${PROJECT_NAME} 
    PUBLIC ${POPPLER_CPP_CFLAGS_OTHER})

install(FILES include/wrapper/wrapper.h  DESTINATION include)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h"  DESTINATION include)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)