add_executable(test_app test.c)

target_link_libraries(test_app
    "${PROJECT_NAME}_lib"
    unity
)

set_target_properties(test_app PROPERTIES
    C_STANDARD 11
)

target_include_directories(test_app PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/hfg
    ${CMAKE_SOURCE_DIR}/extern/glad/include
    ${CMAKE_SOURCE_DIR}/extern/glfw/include
    ${CMAKE_SOURCE_DIR}/hfg/extern/stb
)

add_test(test test_app)
