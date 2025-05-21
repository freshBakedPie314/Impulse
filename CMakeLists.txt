cmake_minimum_required(VERSION 3.15)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dependencies/GLEW/include)
set(GLEW_LIB ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/glew32s.lib)

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include)
set(GLFW_LIB ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib)

project(Impulse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM Win32)  # Ensure 32-bit
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Core/Window
    ${CMAKE_SOURCE_DIR}/src/Utilities/Maths
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

add_subdirectory(src/Utilities)
add_subdirectory(src/Systems/RendererSystem)
add_subdirectory(src/Core)
add_subdirectory(src/Core/Window)
add_subdirectory(src/Entities)
add_subdirectory(src/App)
