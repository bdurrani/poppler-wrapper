project(wrapper VERSION 0.0.1)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(BUILD_SHARED_LIBS YES)
configure_file(wrapper_version.h.in wrapper_version.h @ONLY)
add_library(${PROJECT_NAME} wrapper.cpp)

# define an alias to avoid any potential issues
# with target_link_libraries
add_library(lib::poppler_wrapper ALIAS ${PROJECT_NAME})

# skip setting the version
# we only want a version-less shared lib
# source: https://stackoverflow.com/questions/11866597/how-to-prevent-cmake-from-creating-a-symlink-for-shared-libraries-on-install
# set_target_properties(${PROJECT_NAME} PROPERTIES
    # VERSION ${wrapper_VERSION}
    # SOVERSION ${wrapper_VERSION}
# )

# source: https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
find_package(PkgConfig REQUIRED)

# pkg_search_modules() stops at the first module that matches
# pkg_check_modules() checks all the modules in it's args
pkg_check_modules(poppler-cpp REQUIRED IMPORTED_TARGET poppler-cpp)


target_link_libraries(${PROJECT_NAME} 
    # prefer to statically link poppler
    # the other option would be POPPLER_LIBRARIES
    # PRIVATE ${POPPLER_CPP_STATIC_LIBRARIES}
    PRIVATE PkgConfig::poppler-cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    # Include output from pkg_config
    # PUBLIC ${POPPLER_CPP_INCLUDE_DIRS}
    # Need to add this to use 
    # generated export headers
    ${PROJECT_BINARY_DIR}
)

# target_compile_options(${PROJECT_NAME} 
#     PUBLIC ${POPPLER_CPP_CFLAGS_OTHER})

# add these lines to allow exporting symbols
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME})

install(FILES include/wrapper/wrapper.h  
    DESTINATION include
)

install(FILES 
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h" 
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_version.h" 
    DESTINATION include
)
