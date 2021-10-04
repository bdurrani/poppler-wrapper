project(wrapper VERSION 0.0.1)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(BUILD_SHARED_LIBS YES)

configure_file(wrapper_version.h.in wrapper_version.h @ONLY)

set(POPPLER_CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install")

include(ExternalProject)

SET(POPPLER_CPP_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/install/include/poppler/cpp")
SET(POPPLER_CPP_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/install/lib)

if(UNIX)
  SET(BUILD_BYPRODUCTS ${POPPLER_CPP_LIB_DIR}/libpoppler-cpp.so)
#   ${POPPLER_CPP_LIB_DIR}/libpoppler.a)
endif()

# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

ExternalProject_Add(PopplerDownload
  URL https://poppler.freedesktop.org/poppler-21.10.0.tar.xz
  BUILD_ALWAYS OFF
  BUILD_BYPRODUCTS ${BUILD_BYPRODUCTS}
  CMAKE_ARGS
    -D BUILD_GTK_TESTS=OFF
    -D BUILD_QT5_TESTS=OFF
    -D ENABLE_QT5=OFF
    -D ENABLE_QT6=OFF
    -D ENABLE_GLIB=OFF
    -D BUILD_SHARED_LIBS=ON
    -D ENABLE_GOBJECT_INTROSPECTION=OFF
    -D CMAKE_BUILD_TYPE=Release
    -D CMAKE_POSITION_INDEPENDENT_CODE=ON
    -D CMAKE_INSTALL_PREFIX:PATH=${POPPLER_CMAKE_INSTALL_PREFIX}
)

message("Poppler includes ${POPPLER_CPP_INCLUDE_DIR}}")
message("Poppler libs ${BUILD_BYPRODUCTS}}")
file(MAKE_DIRECTORY ${POPPLER_CPP_INCLUDE_DIR})

add_library(Poppler::Cpp SHARED IMPORTED)
set_target_properties(Poppler::Cpp 
PROPERTIES 
  IMPORTED_LOCATION ${BUILD_BYPRODUCTS}
  INTERFACE_INCLUDE_DIRECTORIES "${POPPLER_CPP_INCLUDE_DIR}"
  POSITION_INDEPENDENT_CODE ON
  )

add_library(Poppler::Plain SHARED IMPORTED)
set_target_properties(Poppler::Plain
PROPERTIES 
  IMPORTED_LOCATION ${POPPLER_CPP_LIB_DIR}/libpoppler.so
  )

add_library(${PROJECT_NAME} 
    document.cpp
    page.cpp
)


# define an alias to avoid any potential issues
# with target_link_libraries
add_library(lib::poppler_wrapper ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} PopplerDownload)

# skip setting the version
# we only want a version-less shared lib
# source: https://stackoverflow.com/questions/11866597/how-to-prevent-cmake-from-creating-a-symlink-for-shared-libraries-on-install
# set_target_properties(${PROJECT_NAME} PROPERTIES
    # VERSION ${wrapper_VERSION}
    # SOVERSION ${wrapper_VERSION}
# )

# source: https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
# find_package(PkgConfig REQUIRED)

# pkg_search_modules() stops at the first module that matches
# pkg_check_modules() checks all the modules in it's args
# pkg_check_modules(POPPLER-CPP REQUIRED IMPORTED_TARGET poppler-cpp)
# pkg_check_modules(POPPLER REQUIRED IMPORTED_TARGET poppler)

target_link_libraries(${PROJECT_NAME} 
    # prefer to statically link poppler
    # the other option would be POPPLER_LIBRARIES
    # PRIVATE ${POPPLER_CPP_STATIC_LIBRARIES}
    # PRIVATE PkgConfig::POPPLER-CPP
    # PRIVATE PkgConfig::POPPLER
    PRIVATE Poppler::Cpp
    PRIVATE Poppler::Plain
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    # Include output from pkg_config
    # PUBLIC ${POPPLER_CPP_INCLUDE_DIRS}
    # Need to add this to use 
    # generated export headers
    PUBLIC ${PROJECT_BINARY_DIR}
)

# use target_compile_definitions() to set up
# custom defines for your target

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
