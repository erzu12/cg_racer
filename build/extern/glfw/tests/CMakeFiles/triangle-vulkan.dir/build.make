# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonas/dev/spaceracer-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonas/dev/spaceracer-c/build

# Include any dependencies generated for this target.
include extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/compiler_depend.make

# Include the progress variables for this target.
include extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make
extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: /home/jonas/dev/spaceracer-c/extern/glfw/tests/triangle-vulkan.c
extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o -MF CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.d -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o -c /home/jonas/dev/spaceracer-c/extern/glfw/tests/triangle-vulkan.c

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jonas/dev/spaceracer-c/extern/glfw/tests/triangle-vulkan.c > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jonas/dev/spaceracer-c/extern/glfw/tests/triangle-vulkan.c -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make
extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_vulkan.c
extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o -MF CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.d -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o -c /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_vulkan.c

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_vulkan.c > CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_vulkan.c -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s

# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o" \
"CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

extern/glfw/tests/triangle-vulkan: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
extern/glfw/tests/triangle-vulkan: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o
extern/glfw/tests/triangle-vulkan: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/build.make
extern/glfw/tests/triangle-vulkan: extern/glfw/src/libglfw3.a
extern/glfw/tests/triangle-vulkan: /usr/lib/libm.so
extern/glfw/tests/triangle-vulkan: /usr/lib/librt.a
extern/glfw/tests/triangle-vulkan: /usr/lib/libm.so
extern/glfw/tests/triangle-vulkan: /usr/lib/libX11.so
extern/glfw/tests/triangle-vulkan: extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable triangle-vulkan"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/build: extern/glfw/tests/triangle-vulkan
.PHONY : extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/build

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/clean

extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd /home/jonas/dev/spaceracer-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonas/dev/spaceracer-c /home/jonas/dev/spaceracer-c/extern/glfw/tests /home/jonas/dev/spaceracer-c/build /home/jonas/dev/spaceracer-c/build/extern/glfw/tests /home/jonas/dev/spaceracer-c/build/extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend

