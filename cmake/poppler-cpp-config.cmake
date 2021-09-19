find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_POPPLER_CPP REQUIRED poppler-cpp)

find_path(popplerCpp_INCLUDE_DIR
    PATHS ${PC_POPPLER_CPP_INCLUDE_DIRS}
    PATH_SUFFIXES popplerCpp
)

set(popplerCpp_VERSION ${PC_POPPLER_CPP_VERSION})
mark_as_advanced(popplerCpp_FOUND popplerCpp_INCLUDE_DIR popplerCpp_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(poppler-cpp
    REQUIRED_VARS popplerCpp_INCLUDE_DIR
    VERSION_VAR popplerCpp_VERSION
)

if(PC_POPPLER_CPP_FOUND)
  set(popplerCpp_INCLUDE_DIRS ${PC_POPPLER_CPP_INCLUDE_DIRS})
endif()

if(PC_POPPLER_CPP_FOUND AND NOT TARGET poppler::Cpp)
  add_library(poppler::Cpp INTERFACE IMPORTED)
  set_target_properties(poppler::Cpp PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${popplerCpp_INCLUDE_DIRS}"
    )
endif()

target_link_libraries(${PROJECT_NAME} 
    # prefer to statically link poppler
    # the other option would be POPPLER_LIBRARIES
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
