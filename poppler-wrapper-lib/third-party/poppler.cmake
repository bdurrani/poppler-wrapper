set(CMAKE_INSTALL_PREFIX
    "${CMAKE_BINARY_DIR}/install"
    CACHE STRING "Final install location." FORCE)

project(build_poppler_release)

include(ExternalProject)

SET(POPPLER_CPP_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/install/include/poppler/cpp")
SET(POPPLER_CPP_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/install/lib)
if(UNIX)
  SET(BUILD_BYPRODUCTS ${POPPLER_CPP_LIB_DIR}/libpoppler-cpp.a)
endif()

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
    -D BUILD_SHARED_LIBS=OFF
    -D CMAKE_BUILD_TYPE=Release
    -D CMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
)

file(MAKE_DIRECTORY ${POPPLER_CPP_INCLUDE_DIR})
add_library(Poppler::Release::Cpp SHARED IMPORTED)
set_target_properties(Poppler::Release::Cpp 
PROPERTIES 
  IMPORTED_LOCATION ${BUILD_BYPRODUCTS}
  INTERFACE_INCLUDE_DIRECTORIES "${POPPLER_CPP_INCLUDE_DIR}"
  )