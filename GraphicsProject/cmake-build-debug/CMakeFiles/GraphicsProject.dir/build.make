# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2017.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2017.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Study\C\GraphicsProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Study\C\GraphicsProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GraphicsProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GraphicsProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GraphicsProject.dir/flags.make

CMakeFiles/GraphicsProject.dir/test.cpp.obj: CMakeFiles/GraphicsProject.dir/flags.make
CMakeFiles/GraphicsProject.dir/test.cpp.obj: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Study\C\GraphicsProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GraphicsProject.dir/test.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GraphicsProject.dir\test.cpp.obj -c D:\Study\C\GraphicsProject\test.cpp

CMakeFiles/GraphicsProject.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GraphicsProject.dir/test.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Study\C\GraphicsProject\test.cpp > CMakeFiles\GraphicsProject.dir\test.cpp.i

CMakeFiles/GraphicsProject.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GraphicsProject.dir/test.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Study\C\GraphicsProject\test.cpp -o CMakeFiles\GraphicsProject.dir\test.cpp.s

CMakeFiles/GraphicsProject.dir/test.cpp.obj.requires:

.PHONY : CMakeFiles/GraphicsProject.dir/test.cpp.obj.requires

CMakeFiles/GraphicsProject.dir/test.cpp.obj.provides: CMakeFiles/GraphicsProject.dir/test.cpp.obj.requires
	$(MAKE) -f CMakeFiles\GraphicsProject.dir\build.make CMakeFiles/GraphicsProject.dir/test.cpp.obj.provides.build
.PHONY : CMakeFiles/GraphicsProject.dir/test.cpp.obj.provides

CMakeFiles/GraphicsProject.dir/test.cpp.obj.provides.build: CMakeFiles/GraphicsProject.dir/test.cpp.obj


# Object files for target GraphicsProject
GraphicsProject_OBJECTS = \
"CMakeFiles/GraphicsProject.dir/test.cpp.obj"

# External object files for target GraphicsProject
GraphicsProject_EXTERNAL_OBJECTS =

GraphicsProject.exe: CMakeFiles/GraphicsProject.dir/test.cpp.obj
GraphicsProject.exe: CMakeFiles/GraphicsProject.dir/build.make
GraphicsProject.exe: CMakeFiles/GraphicsProject.dir/linklibs.rsp
GraphicsProject.exe: CMakeFiles/GraphicsProject.dir/objects1.rsp
GraphicsProject.exe: CMakeFiles/GraphicsProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Study\C\GraphicsProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GraphicsProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GraphicsProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GraphicsProject.dir/build: GraphicsProject.exe

.PHONY : CMakeFiles/GraphicsProject.dir/build

CMakeFiles/GraphicsProject.dir/requires: CMakeFiles/GraphicsProject.dir/test.cpp.obj.requires

.PHONY : CMakeFiles/GraphicsProject.dir/requires

CMakeFiles/GraphicsProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GraphicsProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GraphicsProject.dir/clean

CMakeFiles/GraphicsProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Study\C\GraphicsProject D:\Study\C\GraphicsProject D:\Study\C\GraphicsProject\cmake-build-debug D:\Study\C\GraphicsProject\cmake-build-debug D:\Study\C\GraphicsProject\cmake-build-debug\CMakeFiles\GraphicsProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GraphicsProject.dir/depend
