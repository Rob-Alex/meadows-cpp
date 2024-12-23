# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/robbiealexander/Projects/Cpp/meadows

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/robbiealexander/Projects/Cpp/meadows/build

# Utility rule file for copy_shaders.

# Include any custom commands dependencies for this target.
include shaders/CMakeFiles/copy_shaders.dir/compiler_depend.make

# Include the progress variables for this target.
include shaders/CMakeFiles/copy_shaders.dir/progress.make

shaders/CMakeFiles/copy_shaders:
	cd /Users/robbiealexander/Projects/Cpp/meadows/build/shaders && /usr/local/bin/cmake -E copy /Users/robbiealexander/Projects/Cpp/meadows/build/shaders/compute.metallib /Users/robbiealexander/Projects/Cpp/meadows/build/shaders/compute.metallib
	cd /Users/robbiealexander/Projects/Cpp/meadows/build/shaders && /usr/local/bin/cmake -E copy /Users/robbiealexander/Projects/Cpp/meadows/build/shaders/shader.metallib /Users/robbiealexander/Projects/Cpp/meadows/build/shaders/shader.metallib

copy_shaders: shaders/CMakeFiles/copy_shaders
copy_shaders: shaders/CMakeFiles/copy_shaders.dir/build.make
.PHONY : copy_shaders

# Rule to build all files generated by this target.
shaders/CMakeFiles/copy_shaders.dir/build: copy_shaders
.PHONY : shaders/CMakeFiles/copy_shaders.dir/build

shaders/CMakeFiles/copy_shaders.dir/clean:
	cd /Users/robbiealexander/Projects/Cpp/meadows/build/shaders && $(CMAKE_COMMAND) -P CMakeFiles/copy_shaders.dir/cmake_clean.cmake
.PHONY : shaders/CMakeFiles/copy_shaders.dir/clean

shaders/CMakeFiles/copy_shaders.dir/depend:
	cd /Users/robbiealexander/Projects/Cpp/meadows/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/robbiealexander/Projects/Cpp/meadows /Users/robbiealexander/Projects/Cpp/meadows/shaders /Users/robbiealexander/Projects/Cpp/meadows/build /Users/robbiealexander/Projects/Cpp/meadows/build/shaders /Users/robbiealexander/Projects/Cpp/meadows/build/shaders/CMakeFiles/copy_shaders.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : shaders/CMakeFiles/copy_shaders.dir/depend

