file(GLOB_RECURSE PHYSICS_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(PhysicsSystem STATIC ${PHYSICS_SOURCES})

target_include_directories(PhysicsSystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

target_link_libraries(PhysicsSystem PUBLIC
    ${GLEW_LIB}
    ${GLFW_LIB}
    opengl32.lib
)

target_compile_definitions(PhysicsSystem PUBLIC GLEW_STATIC)
