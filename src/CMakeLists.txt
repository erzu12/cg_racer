file(GLOB_RECURSE SOURCES
    *.c
    *.h
)

list(FILTER SOURCES EXCLUDE REGEX ".*main.c$")

add_executable("${PROJECT_NAME}"
    main.c
)

add_library("${PROJECT_NAME}_lib"
    ${SOURCES}
)

set_property(TARGET "${PROJECT_NAME}" PROPERTY C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries("${PROJECT_NAME}_lib"
    glad
    -lglfw
    hfg
)

target_link_libraries("${PROJECT_NAME}"
    "${PROJECT_NAME}_lib"
)

target_include_directories("${PROJECT_NAME}"
    PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/includes
    PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/includes
    PUBLIC ${CMAKE_SOURCE_DIR}/hfg
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC extern
)
