file(GLOB_RECURSE RENDER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(RendererSystem STATIC ${RENDER_SOURCES})

target_include_directories(RendererSystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

target_link_libraries(RendererSystem PUBLIC
    ${GLEW_LIB}
    ${GLFW_LIB}
    opengl32.lib
)

target_compile_definitions(RendererSystem PUBLIC GLEW_STATIC)
