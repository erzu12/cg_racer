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
include extern/glfw/tests/CMakeFiles/empty.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include extern/glfw/tests/CMakeFiles/empty.dir/compiler_depend.make

# Include the progress variables for this target.
include extern/glfw/tests/CMakeFiles/empty.dir/progress.make

# Include the compile flags for this target's objects.
include extern/glfw/tests/CMakeFiles/empty.dir/flags.make

extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o: extern/glfw/tests/CMakeFiles/empty.dir/flags.make
extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o: /home/jonas/dev/spaceracer-c/extern/glfw/tests/empty.c
extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o: extern/glfw/tests/CMakeFiles/empty.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o -MF CMakeFiles/empty.dir/empty.c.o.d -o CMakeFiles/empty.dir/empty.c.o -c /home/jonas/dev/spaceracer-c/extern/glfw/tests/empty.c

extern/glfw/tests/CMakeFiles/empty.dir/empty.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/empty.dir/empty.c.i"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jonas/dev/spaceracer-c/extern/glfw/tests/empty.c > CMakeFiles/empty.dir/empty.c.i

extern/glfw/tests/CMakeFiles/empty.dir/empty.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/empty.dir/empty.c.s"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jonas/dev/spaceracer-c/extern/glfw/tests/empty.c -o CMakeFiles/empty.dir/empty.c.s

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: extern/glfw/tests/CMakeFiles/empty.dir/flags.make
extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: /home/jonas/dev/spaceracer-c/extern/glfw/deps/tinycthread.c
extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: extern/glfw/tests/CMakeFiles/empty.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o -MF CMakeFiles/empty.dir/__/deps/tinycthread.c.o.d -o CMakeFiles/empty.dir/__/deps/tinycthread.c.o -c /home/jonas/dev/spaceracer-c/extern/glfw/deps/tinycthread.c

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/empty.dir/__/deps/tinycthread.c.i"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jonas/dev/spaceracer-c/extern/glfw/deps/tinycthread.c > CMakeFiles/empty.dir/__/deps/tinycthread.c.i

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/empty.dir/__/deps/tinycthread.c.s"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jonas/dev/spaceracer-c/extern/glfw/deps/tinycthread.c -o CMakeFiles/empty.dir/__/deps/tinycthread.c.s

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o: extern/glfw/tests/CMakeFiles/empty.dir/flags.make
extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o: /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_gl.c
extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o: extern/glfw/tests/CMakeFiles/empty.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o -MF CMakeFiles/empty.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/empty.dir/__/deps/glad_gl.c.o -c /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_gl.c

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/empty.dir/__/deps/glad_gl.c.i"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_gl.c > CMakeFiles/empty.dir/__/deps/glad_gl.c.i

extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/empty.dir/__/deps/glad_gl.c.s"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jonas/dev/spaceracer-c/extern/glfw/deps/glad_gl.c -o CMakeFiles/empty.dir/__/deps/glad_gl.c.s

# Object files for target empty
empty_OBJECTS = \
"CMakeFiles/empty.dir/empty.c.o" \
"CMakeFiles/empty.dir/__/deps/tinycthread.c.o" \
"CMakeFiles/empty.dir/__/deps/glad_gl.c.o"

# External object files for target empty
empty_EXTERNAL_OBJECTS =

extern/glfw/tests/empty: extern/glfw/tests/CMakeFiles/empty.dir/empty.c.o
extern/glfw/tests/empty: extern/glfw/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o
extern/glfw/tests/empty: extern/glfw/tests/CMakeFiles/empty.dir/__/deps/glad_gl.c.o
extern/glfw/tests/empty: extern/glfw/tests/CMakeFiles/empty.dir/build.make
extern/glfw/tests/empty: extern/glfw/src/libglfw3.a
extern/glfw/tests/empty: /usr/lib/libm.so
extern/glfw/tests/empty: /usr/lib/librt.a
extern/glfw/tests/empty: /usr/lib/libX11.so
extern/glfw/tests/empty: extern/glfw/tests/CMakeFiles/empty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable empty"
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/empty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/glfw/tests/CMakeFiles/empty.dir/build: extern/glfw/tests/empty
.PHONY : extern/glfw/tests/CMakeFiles/empty.dir/build

extern/glfw/tests/CMakeFiles/empty.dir/clean:
	cd /home/jonas/dev/spaceracer-c/build/extern/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/empty.dir/cmake_clean.cmake
.PHONY : extern/glfw/tests/CMakeFiles/empty.dir/clean

extern/glfw/tests/CMakeFiles/empty.dir/depend:
	cd /home/jonas/dev/spaceracer-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonas/dev/spaceracer-c /home/jonas/dev/spaceracer-c/extern/glfw/tests /home/jonas/dev/spaceracer-c/build /home/jonas/dev/spaceracer-c/build/extern/glfw/tests /home/jonas/dev/spaceracer-c/build/extern/glfw/tests/CMakeFiles/empty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/glfw/tests/CMakeFiles/empty.dir/depend

