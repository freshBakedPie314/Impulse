file(GLOB_RECURSE UTILITY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Utilities STATIC ${UTILITY_SOURCES})

target_include_directories(Utilities PUBLIC
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

target_link_libraries(Utilities PUBLIC
    ${GLEW_LIB}
    ${GLFW_LIB}
    opengl32.lib
    glu32.lib
)

target_compile_definitions(Utilities PUBLIC GLEW_STATIC)