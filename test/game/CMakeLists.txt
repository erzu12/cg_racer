project(test_game_${PROJECT_NAME})

# User-defined variables
set(UNITY_SRC ${CMAKE_SOURCE_DIR}/Unity/src/unity.c)
set(CMOCK_RUBY_SCRIPT ${CMAKE_SOURCE_DIR}/CMock/lib/cmock.rb)


# Include Unity and CMock headers
include_directories(${CMAKE_SOURCE_DIR}/Unity/src)
include_directories(${CMAKE_SOURCE_DIR}/CMock/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/mocks)

# Enable CTest

# Add test executable
add_executable(${PROJECT_NAME}
    test.c
    ${CMAKE_SOURCE_DIR}/src/game.c
    ${UNITY_SRC}
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
    hfg
    m
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
