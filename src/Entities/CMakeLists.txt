file(GLOB_RECURSE ENTITY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Entities STATIC ${ENTITY_SOURCES})
target_include_directories(Entities PUBLIC
    ${CMAKE_SOURCE_DIR}/src/Utilities
)
target_link_libraries(Entities PUBLIC Utilities)
