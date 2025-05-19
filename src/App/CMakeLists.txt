add_executable(Impulse App.cpp)

target_include_directories(Impulse PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Entities
)

target_link_libraries(Impulse PUBLIC Entities)
target_link_libraries(Impulse PUBLIC RendererSystem)
target_link_libraries(Impulse PUBLIC Core)
target_link_libraries(Impulse PUBLIC Utilities)
