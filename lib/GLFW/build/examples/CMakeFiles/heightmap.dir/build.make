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
include examples/CMakeFiles/heightmap.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/heightmap.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/heightmap.dir/flags.make

examples/CMakeFiles/heightmap.dir/heightmap.c.obj: examples/CMakeFiles/heightmap.dir/flags.make
examples/CMakeFiles/heightmap.dir/heightmap.c.obj: examples/CMakeFiles/heightmap.dir/includes_C.rsp
examples/CMakeFiles/heightmap.dir/heightmap.c.obj: ../examples/heightmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/heightmap.dir/heightmap.c.obj"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\heightmap.dir\heightmap.c.obj   -c C:\Users\Gabriel\Documents\C++\glfw-3.1.2\examples\heightmap.c

examples/CMakeFiles/heightmap.dir/heightmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/heightmap.c.i"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gabriel\Documents\C++\glfw-3.1.2\examples\heightmap.c > CMakeFiles\heightmap.dir\heightmap.c.i

examples/CMakeFiles/heightmap.dir/heightmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/heightmap.c.s"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gabriel\Documents\C++\glfw-3.1.2\examples\heightmap.c -o CMakeFiles\heightmap.dir\heightmap.c.s

examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires:

.PHONY : examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires

examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides: examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires
	$(MAKE) -f examples\CMakeFiles\heightmap.dir\build.make examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides.build
.PHONY : examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides

examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides.build: examples/CMakeFiles/heightmap.dir/heightmap.c.obj


examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: examples/CMakeFiles/heightmap.dir/flags.make
examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: examples/CMakeFiles/heightmap.dir/includes_C.rsp
examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: ../deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\heightmap.dir\__\deps\glad.c.obj   -c C:\Users\Gabriel\Documents\C++\glfw-3.1.2\deps\glad.c

examples/CMakeFiles/heightmap.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/__/deps/glad.c.i"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gabriel\Documents\C++\glfw-3.1.2\deps\glad.c > CMakeFiles\heightmap.dir\__\deps\glad.c.i

examples/CMakeFiles/heightmap.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/__/deps/glad.c.s"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gabriel\Documents\C++\glfw-3.1.2\deps\glad.c -o CMakeFiles\heightmap.dir\__\deps\glad.c.s

examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires:

.PHONY : examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires

examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides: examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires
	$(MAKE) -f examples\CMakeFiles\heightmap.dir\build.make examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides.build
.PHONY : examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides

examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides.build: examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj


# Object files for target heightmap
heightmap_OBJECTS = \
"CMakeFiles/heightmap.dir/heightmap.c.obj" \
"CMakeFiles/heightmap.dir/__/deps/glad.c.obj"

# External object files for target heightmap
heightmap_EXTERNAL_OBJECTS =

examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/heightmap.c.obj
examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj
examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/build.make
examples/heightmap.exe: src/glfw3dll.a
examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/linklibs.rsp
examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/objects1.rsp
examples/heightmap.exe: examples/CMakeFiles/heightmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable heightmap.exe"
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\heightmap.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/heightmap.dir/build: examples/heightmap.exe

.PHONY : examples/CMakeFiles/heightmap.dir/build

examples/CMakeFiles/heightmap.dir/requires: examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires
examples/CMakeFiles/heightmap.dir/requires: examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires

.PHONY : examples/CMakeFiles/heightmap.dir/requires

examples/CMakeFiles/heightmap.dir/clean:
	cd /d C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples && $(CMAKE_COMMAND) -P CMakeFiles\heightmap.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/heightmap.dir/clean

examples/CMakeFiles/heightmap.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Gabriel\Documents\C++\glfw-3.1.2 C:\Users\Gabriel\Documents\C++\glfw-3.1.2\examples C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples C:\Users\Gabriel\Documents\C++\glfw-3.1.2\build\examples\CMakeFiles\heightmap.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/heightmap.dir/depend
