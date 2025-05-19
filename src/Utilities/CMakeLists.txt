file(GLOB_RECURSE UTILITY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Utilities STATIC ${UTILITY_SOURCES})

target_include_directories(Utilities PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/dependencies/GLEW/include
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include
)

target_link_libraries(Utilities PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/glew32s.lib
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib
    opengl32.lib
)

target_compile_definitions(Utilities PUBLIC GLEW_STATIC)