cmake_minimum_required(VERSION 3.16.2)

project(hfg)

add_subdirectory(extern/stb)

file(GLOB_RECURSE hfg_SRC
    "*.c"
    "*.h"
)

add_library("${PROJECT_NAME}"
    ${hfg_SRC}
)

set_property(TARGET "${PROJECT_NAME}" PROPERTY C_STANDARD 11)
set_target_properties("${PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE C)

target_include_directories("${PROJECT_NAME}"
	PUBLIC ${CMAKE_SOURCE_DIR}/extern/glad/include
	PUBLIC ${CMAKE_SOURCE_DIR}/extern/glfw/include
    PUBLIC ${PROJECT_SOURCE_DIR}/extern/stb
    PUBLIC ${CMAKE_SOURCE_DIR}/hfg
	PUBLIC ${CMAKE_SOURCE_DIR}/
)

target_link_libraries("${PROJECT_NAME}"
    glfw
	glad
    stb
    m
)
