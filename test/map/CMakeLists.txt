project(test_map_${PROJECT_NAME})

# User-defined variables
set(UNITY_SRC ${CMAKE_SOURCE_DIR}/Unity/src/unity.c)
set(CMOCK_RUBY_SCRIPT ${CMAKE_SOURCE_DIR}/CMock/lib/cmock.rb)


# Include Unity and CMock headers
include_directories(${CMAKE_SOURCE_DIR}/Unity/src)
include_directories(${CMAKE_SOURCE_DIR}/CMock/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/mocks)

# Enable CTest

message(STATUS "Generating mocks for window.h")
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mocks/Mockwindow.c
    COMMAND ruby ${CMOCK_RUBY_SCRIPT} -o${CMAKE_SOURCE_DIR}/cmock_config.yml ${CMAKE_SOURCE_DIR}/src/window.h
    DEPENDS ${CMAKE_SOURCE_DIR}/src/window.h
)

message(STATUS "Generating mocks for 2dGraphics.h")
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mocks/Mock2dGraphics.c
    COMMAND ruby ${CMOCK_RUBY_SCRIPT} -o${CMAKE_SOURCE_DIR}/cmock_config.yml ${CMAKE_SOURCE_DIR}/hfg/2dGraphics.h
    DEPENDS ${CMAKE_SOURCE_DIR}/hfg/2dGraphics.h
)

# Add test executable
add_executable(${PROJECT_NAME}
    test.c
    ${CMAKE_SOURCE_DIR}/src/map.c
    ${UNITY_SRC}
    ${CMAKE_CURRENT_BINARY_DIR}/mocks/Mockwindow.c
    ${CMAKE_CURRENT_BINARY_DIR}/mocks/Mock2dGraphics.c
    ${CMAKE_SOURCE_DIR}/hfg/2dMath.c
    ${CMAKE_SOURCE_DIR}/hfg/2dPhysics.c
    ${CMAKE_SOURCE_DIR}/hfg/2dSpline.c
    ${CMAKE_SOURCE_DIR}/CMock/src/cmock.c
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/extern/glad/include
    PUBLIC ${CMAKE_SOURCE_DIR}/hfg/extern/stb
    PUBLIC ${CMAKE_SOURCE_DIR}/hfg
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC extern
)

target_link_libraries(${PROJECT_NAME} 
    m
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
