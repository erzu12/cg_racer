cmake_minimum_required(VERSION 3.16.2)

project(spaceracer)

add_subdirectory(hfg)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)


add_executable("${PROJECT_NAME}"
    "spaceracer.c"
)

set_property(TARGET "${PROJECT_NAME}" PROPERTY C_STANDARD 11)

target_link_libraries("${PROJECT_NAME}"
	glad
	glfw
    hfg
)

target_include_directories("${PROJECT_NAME}"
	PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/includes
	PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/includes
	PUBLIC ${CMAKE_SOURCE_DIR}/hfg
	PUBLIC extern
)
