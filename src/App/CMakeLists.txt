add_executable(Impulse App.cpp)

target_link_libraries(Impulse PUBLIC RendererSystem)
target_link_libraries(Impulse PUBLIC Core)
target_link_libraries(Impulse PUBLIC Entities)
target_link_libraries(Impulse PUBLIC Utilities)
