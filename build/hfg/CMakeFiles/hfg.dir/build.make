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
include hfg/CMakeFiles/hfg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include hfg/CMakeFiles/hfg.dir/compiler_depend.make

# Include the progress variables for this target.
include hfg/CMakeFiles/hfg.dir/progress.make

# Include the compile flags for this target's objects.
include hfg/CMakeFiles/hfg.dir/flags.make

# Object files for target hfg
hfg_OBJECTS =

# External object files for target hfg
hfg_EXTERNAL_OBJECTS =

hfg/libhfg.a: hfg/CMakeFiles/hfg.dir/build.make
hfg/libhfg.a: hfg/CMakeFiles/hfg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jonas/dev/spaceracer-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking C static library libhfg.a"
	cd /home/jonas/dev/spaceracer-c/build/hfg && $(CMAKE_COMMAND) -P CMakeFiles/hfg.dir/cmake_clean_target.cmake
	cd /home/jonas/dev/spaceracer-c/build/hfg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hfg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hfg/CMakeFiles/hfg.dir/build: hfg/libhfg.a
.PHONY : hfg/CMakeFiles/hfg.dir/build

hfg/CMakeFiles/hfg.dir/clean:
	cd /home/jonas/dev/spaceracer-c/build/hfg && $(CMAKE_COMMAND) -P CMakeFiles/hfg.dir/cmake_clean.cmake
.PHONY : hfg/CMakeFiles/hfg.dir/clean

hfg/CMakeFiles/hfg.dir/depend:
	cd /home/jonas/dev/spaceracer-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonas/dev/spaceracer-c /home/jonas/dev/spaceracer-c/hfg /home/jonas/dev/spaceracer-c/build /home/jonas/dev/spaceracer-c/build/hfg /home/jonas/dev/spaceracer-c/build/hfg/CMakeFiles/hfg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hfg/CMakeFiles/hfg.dir/depend

