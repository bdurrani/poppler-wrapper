project(wrapper)
add_library(${PROJECT_NAME} STATIC wrapper.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)