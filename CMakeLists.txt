cmake_minimum_required(VERSION 3.16.2)

project(gl_gui)

add_subdirectory(hfg)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)

file(GLOB src
    "src/*.cpp"
    "src/*.h"
)

add_executable("${PROJECT_NAME}"
    ${src}
)

set_property(TARGET "${PROJECT_NAME}" PROPERTY CPP_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries("${PROJECT_NAME}"
	glad
	-lglfw
    hfg
)

target_include_directories("${PROJECT_NAME}"
	PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/includes
	PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/includes
	PUBLIC ${CMAKE_SOURCE_DIR}/hfg
	PUBLIC extern
)
