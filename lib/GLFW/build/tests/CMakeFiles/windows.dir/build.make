# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Gabriel\Documents\C++\glfw-3.1.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build

# Include any dependencies generated for this target.
include tests/CMakeFiles/windows.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/windows.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/windows.dir/flags.make

tests/CMakeFiles/windows.dir/windows.c.obj: tests/CMakeFiles/windows.dir/flags.make
tests/CMakeFiles/windows.dir/windows.c.obj: tests/CMakeFiles/windows.dir/includes_C.rsp
tests/CMakeFiles/windows.dir/windows.c.obj: ../tests/windows.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/windows.dir/windows.c.obj"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\windows.dir\windows.c.obj   -c C:\Users\Gabriel\Documents\C++\glfw-3.1.2\tests\windows.c

tests/CMakeFiles/windows.dir/windows.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/windows.dir/windows.c.i"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gabriel\Documents\C++\glfw-3.1.2\tests\windows.c > CMakeFiles\windows.dir\windows.c.i

tests/CMakeFiles/windows.dir/windows.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/windows.dir/windows.c.s"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gabriel\Documents\C++\glfw-3.1.2\tests\windows.c -o CMakeFiles\windows.dir\windows.c.s

tests/CMakeFiles/windows.dir/windows.c.obj.requires:

.PHONY : tests/CMakeFiles/windows.dir/windows.c.obj.requires

tests/CMakeFiles/windows.dir/windows.c.obj.provides: tests/CMakeFiles/windows.dir/windows.c.obj.requires
	$(MAKE) -f tests\CMakeFiles\windows.dir\build.make tests/CMakeFiles/windows.dir/windows.c.obj.provides.build
.PHONY : tests/CMakeFiles/windows.dir/windows.c.obj.provides

tests/CMakeFiles/windows.dir/windows.c.obj.provides.build: tests/CMakeFiles/windows.dir/windows.c.obj


# Object files for target windows
windows_OBJECTS = \
"CMakeFiles/windows.dir/windows.c.obj"

# External object files for target windows
windows_EXTERNAL_OBJECTS =

tests/windows.exe: tests/CMakeFiles/windows.dir/windows.c.obj
tests/windows.exe: tests/CMakeFiles/windows.dir/build.make
tests/windows.exe: src/glfw3dll.a
tests/windows.exe: tests/CMakeFiles/windows.dir/linklibs.rsp
tests/windows.exe: tests/CMakeFiles/windows.dir/objects1.rsp
tests/windows.exe: tests/CMakeFiles/windows.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable windows.exe"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\windows.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/windows.dir/build: tests/windows.exe

.PHONY : tests/CMakeFiles/windows.dir/build

tests/CMakeFiles/windows.dir/requires: tests/CMakeFiles/windows.dir/windows.c.obj.requires

.PHONY : tests/CMakeFiles/windows.dir/requires

tests/CMakeFiles/windows.dir/clean:
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests && $(CMAKE_COMMAND) -P CMakeFiles\windows.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/windows.dir/clean

tests/CMakeFiles/windows.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Gabriel\Documents\C++\glfw-3.1.2 C:\Users\Gabriel\Documents\C++\glfw-3.1.2\tests C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\tests\CMakeFiles\windows.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/windows.dir/depend

