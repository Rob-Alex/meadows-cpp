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
CMAKE_SOURCE_DIR = /Users/robbiealexander/Projects/Cpp/meadows-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/robbiealexander/Projects/Cpp/meadows-cpp/build

# Include any dependencies generated for this target.
include src/CMakeFiles/meadows.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/meadows.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/meadows.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/meadows.dir/flags.make

src/CMakeFiles/meadows.dir/app.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/app.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/app.cpp
src/CMakeFiles/meadows.dir/app.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/meadows.dir/app.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/app.cpp.o -MF CMakeFiles/meadows.dir/app.cpp.o.d -o CMakeFiles/meadows.dir/app.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/app.cpp

src/CMakeFiles/meadows.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/app.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/app.cpp > CMakeFiles/meadows.dir/app.cpp.i

src/CMakeFiles/meadows.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/app.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/app.cpp -o CMakeFiles/meadows.dir/app.cpp.s

src/CMakeFiles/meadows.dir/benchmarking.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/benchmarking.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/benchmarking.cpp
src/CMakeFiles/meadows.dir/benchmarking.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/meadows.dir/benchmarking.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/benchmarking.cpp.o -MF CMakeFiles/meadows.dir/benchmarking.cpp.o.d -o CMakeFiles/meadows.dir/benchmarking.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/benchmarking.cpp

src/CMakeFiles/meadows.dir/benchmarking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/benchmarking.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/benchmarking.cpp > CMakeFiles/meadows.dir/benchmarking.cpp.i

src/CMakeFiles/meadows.dir/benchmarking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/benchmarking.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/benchmarking.cpp -o CMakeFiles/meadows.dir/benchmarking.cpp.s

src/CMakeFiles/meadows.dir/cpu_computer.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/cpu_computer.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/cpu_computer.cpp
src/CMakeFiles/meadows.dir/cpu_computer.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/meadows.dir/cpu_computer.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/cpu_computer.cpp.o -MF CMakeFiles/meadows.dir/cpu_computer.cpp.o.d -o CMakeFiles/meadows.dir/cpu_computer.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/cpu_computer.cpp

src/CMakeFiles/meadows.dir/cpu_computer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/cpu_computer.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/cpu_computer.cpp > CMakeFiles/meadows.dir/cpu_computer.cpp.i

src/CMakeFiles/meadows.dir/cpu_computer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/cpu_computer.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/cpu_computer.cpp -o CMakeFiles/meadows.dir/cpu_computer.cpp.s

src/CMakeFiles/meadows.dir/glfw_adapter.mm.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/glfw_adapter.mm.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/glfw_adapter.mm
src/CMakeFiles/meadows.dir/glfw_adapter.mm.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building OBJCXX object src/CMakeFiles/meadows.dir/glfw_adapter.mm.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) -x objective-c++ $(OBJCXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/glfw_adapter.mm.o -MF CMakeFiles/meadows.dir/glfw_adapter.mm.o.d -o CMakeFiles/meadows.dir/glfw_adapter.mm.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/glfw_adapter.mm

src/CMakeFiles/meadows.dir/glfw_adapter.mm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing OBJCXX source to CMakeFiles/meadows.dir/glfw_adapter.mm.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) $(OBJCXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/glfw_adapter.mm > CMakeFiles/meadows.dir/glfw_adapter.mm.i

src/CMakeFiles/meadows.dir/glfw_adapter.mm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling OBJCXX source to assembly CMakeFiles/meadows.dir/glfw_adapter.mm.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) $(OBJCXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/glfw_adapter.mm -o CMakeFiles/meadows.dir/glfw_adapter.mm.s

src/CMakeFiles/meadows.dir/grid.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/grid.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/grid.cpp
src/CMakeFiles/meadows.dir/grid.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/meadows.dir/grid.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/grid.cpp.o -MF CMakeFiles/meadows.dir/grid.cpp.o.d -o CMakeFiles/meadows.dir/grid.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/grid.cpp

src/CMakeFiles/meadows.dir/grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/grid.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/grid.cpp > CMakeFiles/meadows.dir/grid.cpp.i

src/CMakeFiles/meadows.dir/grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/grid.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/grid.cpp -o CMakeFiles/meadows.dir/grid.cpp.s

src/CMakeFiles/meadows.dir/main.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/main.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/main.cpp
src/CMakeFiles/meadows.dir/main.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/meadows.dir/main.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/main.cpp.o -MF CMakeFiles/meadows.dir/main.cpp.o.d -o CMakeFiles/meadows.dir/main.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/main.cpp

src/CMakeFiles/meadows.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/main.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/main.cpp > CMakeFiles/meadows.dir/main.cpp.i

src/CMakeFiles/meadows.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/main.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/main.cpp -o CMakeFiles/meadows.dir/main.cpp.s

src/CMakeFiles/meadows.dir/mtl_computer.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/mtl_computer.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/mtl_computer.cpp
src/CMakeFiles/meadows.dir/mtl_computer.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/meadows.dir/mtl_computer.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/mtl_computer.cpp.o -MF CMakeFiles/meadows.dir/mtl_computer.cpp.o.d -o CMakeFiles/meadows.dir/mtl_computer.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/mtl_computer.cpp

src/CMakeFiles/meadows.dir/mtl_computer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/mtl_computer.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/mtl_computer.cpp > CMakeFiles/meadows.dir/mtl_computer.cpp.i

src/CMakeFiles/meadows.dir/mtl_computer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/mtl_computer.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/mtl_computer.cpp -o CMakeFiles/meadows.dir/mtl_computer.cpp.s

src/CMakeFiles/meadows.dir/renderer.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/renderer.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/renderer.cpp
src/CMakeFiles/meadows.dir/renderer.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/meadows.dir/renderer.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/renderer.cpp.o -MF CMakeFiles/meadows.dir/renderer.cpp.o.d -o CMakeFiles/meadows.dir/renderer.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/renderer.cpp

src/CMakeFiles/meadows.dir/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/renderer.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/renderer.cpp > CMakeFiles/meadows.dir/renderer.cpp.i

src/CMakeFiles/meadows.dir/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/renderer.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/renderer.cpp -o CMakeFiles/meadows.dir/renderer.cpp.s

src/CMakeFiles/meadows.dir/simulator.cpp.o: src/CMakeFiles/meadows.dir/flags.make
src/CMakeFiles/meadows.dir/simulator.cpp.o: /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/simulator.cpp
src/CMakeFiles/meadows.dir/simulator.cpp.o: src/CMakeFiles/meadows.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/meadows.dir/simulator.cpp.o"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/meadows.dir/simulator.cpp.o -MF CMakeFiles/meadows.dir/simulator.cpp.o.d -o CMakeFiles/meadows.dir/simulator.cpp.o -c /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/simulator.cpp

src/CMakeFiles/meadows.dir/simulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meadows.dir/simulator.cpp.i"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/simulator.cpp > CMakeFiles/meadows.dir/simulator.cpp.i

src/CMakeFiles/meadows.dir/simulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meadows.dir/simulator.cpp.s"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robbiealexander/Projects/Cpp/meadows-cpp/src/simulator.cpp -o CMakeFiles/meadows.dir/simulator.cpp.s

# Object files for target meadows
meadows_OBJECTS = \
"CMakeFiles/meadows.dir/app.cpp.o" \
"CMakeFiles/meadows.dir/benchmarking.cpp.o" \
"CMakeFiles/meadows.dir/cpu_computer.cpp.o" \
"CMakeFiles/meadows.dir/glfw_adapter.mm.o" \
"CMakeFiles/meadows.dir/grid.cpp.o" \
"CMakeFiles/meadows.dir/main.cpp.o" \
"CMakeFiles/meadows.dir/mtl_computer.cpp.o" \
"CMakeFiles/meadows.dir/renderer.cpp.o" \
"CMakeFiles/meadows.dir/simulator.cpp.o"

# External object files for target meadows
meadows_EXTERNAL_OBJECTS =

src/meadows: src/CMakeFiles/meadows.dir/app.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/benchmarking.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/cpu_computer.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/glfw_adapter.mm.o
src/meadows: src/CMakeFiles/meadows.dir/grid.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/main.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/mtl_computer.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/renderer.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/simulator.cpp.o
src/meadows: src/CMakeFiles/meadows.dir/build.make
src/meadows: metal-cmake/libMETAL_CPP.a
src/meadows: /opt/homebrew/lib/libglfw.3.4.dylib
src/meadows: src/CMakeFiles/meadows.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/robbiealexander/Projects/Cpp/meadows-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable meadows"
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/meadows.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/meadows.dir/build: src/meadows
.PHONY : src/CMakeFiles/meadows.dir/build

src/CMakeFiles/meadows.dir/clean:
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src && $(CMAKE_COMMAND) -P CMakeFiles/meadows.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/meadows.dir/clean

src/CMakeFiles/meadows.dir/depend:
	cd /Users/robbiealexander/Projects/Cpp/meadows-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/robbiealexander/Projects/Cpp/meadows-cpp /Users/robbiealexander/Projects/Cpp/meadows-cpp/src /Users/robbiealexander/Projects/Cpp/meadows-cpp/build /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src /Users/robbiealexander/Projects/Cpp/meadows-cpp/build/src/CMakeFiles/meadows.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/meadows.dir/depend

