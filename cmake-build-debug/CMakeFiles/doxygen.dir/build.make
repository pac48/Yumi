# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\paulg\Downloads\catkin\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\paulg\Downloads\catkin\src\cmake-build-debug

# Utility rule file for doxygen.

# Include any custom commands dependencies for this target.
include CMakeFiles\doxygen.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\doxygen.dir\progress.make

doxygen: CMakeFiles\doxygen.dir\build.make
.PHONY : doxygen

# Rule to build all files generated by this target.
CMakeFiles\doxygen.dir\build: doxygen
.PHONY : CMakeFiles\doxygen.dir\build

CMakeFiles\doxygen.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\doxygen.dir\cmake_clean.cmake
.PHONY : CMakeFiles\doxygen.dir\clean

CMakeFiles\doxygen.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\paulg\Downloads\catkin\src C:\Users\paulg\Downloads\catkin\src C:\Users\paulg\Downloads\catkin\src\cmake-build-debug C:\Users\paulg\Downloads\catkin\src\cmake-build-debug C:\Users\paulg\Downloads\catkin\src\cmake-build-debug\CMakeFiles\doxygen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\doxygen.dir\depend

