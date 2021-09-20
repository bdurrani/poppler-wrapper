#[==[
Reference: https://github.com/Kitware/CMake/blob/master/Modules/FindPostgreSQL.cmake

Finds the poppler cpp information via pkg-config
#]==]


find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_POPPLER_CPP REQUIRED poppler-cpp)

set(PopplerCpp_VERSION ${PC_POPPLER_CPP_VERSION})
set(PopplerCpp_INCLUDE_DIRS ${PC_POPPLER_CPP_INCLUDE_DIRS})

if(PC_POPPLER_CPP_FOUND AND NOT TARGET poppler::Cpp)
  add_library(poppler::Cpp INTERFACE IMPORTED)
  set_target_properties(poppler::Cpp PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        INTERFACE_INCLUDE_DIRECTORIES "${PC_POPPLER_CPP_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${PC_POPPLER_CPP_STATIC_LIBRARIES}"
        INTERFACE_COMPILE_OPTIONS "${PC_POPPLER_CPP_CFLAGS}"
        VERSION "${PC_POPPLER_CPP_VERSION}"
    )
ELSE (PC_POPPLER_CPP_FOUND)
    MESSAGE(FATAL_ERROR "Could not find poppler-cpp library")
endif()

mark_as_advanced(PopplerCpp_FOUND PopplerCpp_INCLUDE_DIRS PopplerCpp_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PopplerCpp
    REQUIRED_VARS PopplerCpp_INCLUDE_DIRS
    VERSION_VAR PopplerCpp_VERSION
)

# target_link_libraries(${PROJECT_NAME} 
#     # prefer to statically link poppler
#     # the other option would be POPPLER_LIBRARIES
#     PRIVATE ${POPPLER_CPP_STATIC_LIBRARIES}
# )

# target_include_directories(${PROJECT_NAME} 
#     PUBLIC ${PROJECT_SOURCE_DIR}/include
#     # Include output from pkg_config
#     PUBLIC ${POPPLER_CPP_INCLUDE_DIRS}
#     # Need to add this to use 
#     # generated export headers
#     ${PROJECT_BINARY_DIR}
# )

# target_compile_options(${PROJECT_NAME} 
#     PUBLIC ${POPPLER_CPP_CFLAGS_OTHER})
