# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /export/home/tkaprelian/Software/cmake/cmake-3.16.4-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /export/home/tkaprelian/Software/cmake/cmake-3.16.4-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /export/home/tkaprelian/Software/GatePython/gam-g4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9

# Utility rule file for ContinuousStart.

# Include the progress variables for this target.
include utk/CMakeFiles/ContinuousStart.dir/progress.make

utk/CMakeFiles/ContinuousStart:
	cd /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9/utk && /export/home/tkaprelian/Software/cmake/cmake-3.16.4-Linux-x86_64/bin/ctest -D ContinuousStart

ContinuousStart: utk/CMakeFiles/ContinuousStart
ContinuousStart: utk/CMakeFiles/ContinuousStart.dir/build.make

.PHONY : ContinuousStart

# Rule to build all files generated by this target.
utk/CMakeFiles/ContinuousStart.dir/build: ContinuousStart

.PHONY : utk/CMakeFiles/ContinuousStart.dir/build

utk/CMakeFiles/ContinuousStart.dir/clean:
	cd /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9/utk && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousStart.dir/cmake_clean.cmake
.PHONY : utk/CMakeFiles/ContinuousStart.dir/clean

utk/CMakeFiles/ContinuousStart.dir/depend:
	cd /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /export/home/tkaprelian/Software/GatePython/gam-g4 /export/home/tkaprelian/Software/GatePython/gam-g4/utk /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9 /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9/utk /export/home/tkaprelian/Software/GatePython/gam-g4/build/temp.linux-x86_64-3.9/utk/CMakeFiles/ContinuousStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utk/CMakeFiles/ContinuousStart.dir/depend

