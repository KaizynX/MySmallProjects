# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build

# Include any dependencies generated for this target.
include CMakeFiles/astar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/astar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/astar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/astar.dir/flags.make

CMakeFiles/astar.dir/main.cpp.obj: CMakeFiles/astar.dir/flags.make
CMakeFiles/astar.dir/main.cpp.obj: ../main.cpp
CMakeFiles/astar.dir/main.cpp.obj: CMakeFiles/astar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/astar.dir/main.cpp.obj"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/astar.dir/main.cpp.obj -MF CMakeFiles/astar.dir/main.cpp.obj.d -o CMakeFiles/astar.dir/main.cpp.obj -c C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/main.cpp

CMakeFiles/astar.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/astar.dir/main.cpp.i"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/main.cpp > CMakeFiles/astar.dir/main.cpp.i

CMakeFiles/astar.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/astar.dir/main.cpp.s"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/main.cpp -o CMakeFiles/astar.dir/main.cpp.s

CMakeFiles/astar.dir/process.cpp.obj: CMakeFiles/astar.dir/flags.make
CMakeFiles/astar.dir/process.cpp.obj: ../process.cpp
CMakeFiles/astar.dir/process.cpp.obj: CMakeFiles/astar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/astar.dir/process.cpp.obj"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/astar.dir/process.cpp.obj -MF CMakeFiles/astar.dir/process.cpp.obj.d -o CMakeFiles/astar.dir/process.cpp.obj -c C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/process.cpp

CMakeFiles/astar.dir/process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/astar.dir/process.cpp.i"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/process.cpp > CMakeFiles/astar.dir/process.cpp.i

CMakeFiles/astar.dir/process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/astar.dir/process.cpp.s"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/process.cpp -o CMakeFiles/astar.dir/process.cpp.s

# Object files for target astar
astar_OBJECTS = \
"CMakeFiles/astar.dir/main.cpp.obj" \
"CMakeFiles/astar.dir/process.cpp.obj"

# External object files for target astar
astar_EXTERNAL_OBJECTS =

astar.exe: CMakeFiles/astar.dir/main.cpp.obj
astar.exe: CMakeFiles/astar.dir/process.cpp.obj
astar.exe: CMakeFiles/astar.dir/build.make
astar.exe: CMakeFiles/astar.dir/linklibs.rsp
astar.exe: CMakeFiles/astar.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable astar.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/astar.dir/objects.a
	C:/MinGW/bin/ar.exe qc CMakeFiles/astar.dir/objects.a @CMakeFiles/astar.dir/objects1.rsp
	C:/MinGW/bin/c++.exe -std=c++11 -lpthread -pthread -Wl,--whole-archive CMakeFiles/astar.dir/objects.a -Wl,--no-whole-archive -o astar.exe -Wl,--out-implib,libastar.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/astar.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/astar.dir/build: astar.exe
.PHONY : CMakeFiles/astar.dir/build

CMakeFiles/astar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/astar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/astar.dir/clean

CMakeFiles/astar.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build C:/Users/Kaizyn/Documents/MySmallProjects/astar2021/default_program/build/CMakeFiles/astar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/astar.dir/depend

