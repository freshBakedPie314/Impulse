add_executable(Impulse App.cpp)

target_include_directories(Impulse PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Entities
)

add_custom_command(TARGET Impulse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:Impulse>/res
)

target_link_libraries(Impulse PUBLIC Entities)
target_link_libraries(Impulse PUBLIC Components)
target_link_libraries(Impulse PUBLIC RendererSystem)
target_link_libraries(Impulse PUBLIC Core)
target_link_libraries(Impulse PUBLIC Utilities)
