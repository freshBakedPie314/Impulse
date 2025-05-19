cmake_minimum_required(VERSION 3.15)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(Impulse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM Win32)  # Ensure 32-bit
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



add_subdirectory(src/App)
add_subdirectory(src/Systems/RendererSystem)
add_subdirectory(src/Core)
add_subdirectory(src/Utilities)
add_subdirectory(src/Entities)
