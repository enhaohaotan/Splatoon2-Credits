# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build

# Include any dependencies generated for this target.
include examples/CMakeFiles/splitview.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/splitview.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/splitview.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/splitview.dir/flags.make

examples/CMakeFiles/splitview.dir/splitview.c.obj: examples/CMakeFiles/splitview.dir/flags.make
examples/CMakeFiles/splitview.dir/splitview.c.obj: examples/CMakeFiles/splitview.dir/includes_C.rsp
examples/CMakeFiles/splitview.dir/splitview.c.obj: C:/Users/74132/CLionProjects/Splatoon2-Credits/libraries/glfw/examples/splitview.c
examples/CMakeFiles/splitview.dir/splitview.c.obj: examples/CMakeFiles/splitview.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/splitview.dir/splitview.c.obj"
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/splitview.dir/splitview.c.obj -MF CMakeFiles\splitview.dir\splitview.c.obj.d -o CMakeFiles\splitview.dir\splitview.c.obj -c C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\examples\splitview.c

examples/CMakeFiles/splitview.dir/splitview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/splitview.dir/splitview.c.i"
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\examples\splitview.c > CMakeFiles\splitview.dir\splitview.c.i

examples/CMakeFiles/splitview.dir/splitview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/splitview.dir/splitview.c.s"
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\examples\splitview.c -o CMakeFiles\splitview.dir\splitview.c.s

examples/CMakeFiles/splitview.dir/glfw.rc.obj: examples/CMakeFiles/splitview.dir/flags.make
examples/CMakeFiles/splitview.dir/glfw.rc.obj: C:/Users/74132/CLionProjects/Splatoon2-Credits/libraries/glfw/examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object examples/CMakeFiles/splitview.dir/glfw.rc.obj"
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && C:\msys64\mingw64\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\examples\glfw.rc CMakeFiles\splitview.dir\glfw.rc.obj

# Object files for target splitview
splitview_OBJECTS = \
"CMakeFiles/splitview.dir/splitview.c.obj" \
"CMakeFiles/splitview.dir/glfw.rc.obj"

# External object files for target splitview
splitview_EXTERNAL_OBJECTS =

examples/splitview.exe: examples/CMakeFiles/splitview.dir/splitview.c.obj
examples/splitview.exe: examples/CMakeFiles/splitview.dir/glfw.rc.obj
examples/splitview.exe: examples/CMakeFiles/splitview.dir/build.make
examples/splitview.exe: src/libglfw3.a
examples/splitview.exe: examples/CMakeFiles/splitview.dir/linkLibs.rsp
examples/splitview.exe: examples/CMakeFiles/splitview.dir/objects1.rsp
examples/splitview.exe: examples/CMakeFiles/splitview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable splitview.exe"
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\splitview.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/splitview.dir/build: examples/splitview.exe
.PHONY : examples/CMakeFiles/splitview.dir/build

examples/CMakeFiles/splitview.dir/clean:
	cd /d C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples && $(CMAKE_COMMAND) -P CMakeFiles\splitview.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/splitview.dir/clean

examples/CMakeFiles/splitview.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\examples C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples C:\Users\74132\CLionProjects\Splatoon2-Credits\libraries\glfw\build\examples\CMakeFiles\splitview.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : examples/CMakeFiles/splitview.dir/depend
