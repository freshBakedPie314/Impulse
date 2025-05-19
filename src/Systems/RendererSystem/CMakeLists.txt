file(GLOB_RECURSE RENDER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(RendererSystem STATIC ${RENDER_SOURCES})

target_include_directories(RendererSystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/dependencies/GLEW/include
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include
    ${CMAKE_SOURCE_DIR}/src/Entities
)

target_link_libraries(RendererSystem PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/glew32s.lib
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib
    opengl32.lib
)

target_compile_definitions(RendererSystem PUBLIC GLEW_STATIC)
