cmake_minimum_required(VERSION 3.16.2)

project(spaceracer)


# SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)


#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)  
# We declare a variable to select what to build 
set (TARGET_GROUP production CACHE STRING "What Should I Build?")  # Modules that exist in both our release and our unit tests, are added now   

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(hfg)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs --coverage")
add_subdirectory(src)

if(TARGET_GROUP STREQUAL release) 
    # If we had any files that ONLY were compiled into our release, for example startup code,
    # it's really handy to put it here.  
elseif(TARGET_GROUP STREQUAL test) 
    # It also needs to understand we have code in source and test directories  

    add_subdirectory(test)  
else()    
    message(FATAL_ERROR "I don't know the TARGET_GROUP you gave me!") 
endif()

