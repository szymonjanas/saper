# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/szymon/CppProjects/saper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/szymon/CppProjects/saper/build/Debug

# Include any dependencies generated for this target.
include CMakeFiles/saper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/saper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/saper.dir/flags.make

CMakeFiles/saper.dir/src/main.cpp.o: CMakeFiles/saper.dir/flags.make
CMakeFiles/saper.dir/src/main.cpp.o: ../../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/szymon/CppProjects/saper/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/saper.dir/src/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saper.dir/src/main.cpp.o -c /home/szymon/CppProjects/saper/src/main.cpp

CMakeFiles/saper.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saper.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/szymon/CppProjects/saper/src/main.cpp > CMakeFiles/saper.dir/src/main.cpp.i

CMakeFiles/saper.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saper.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/szymon/CppProjects/saper/src/main.cpp -o CMakeFiles/saper.dir/src/main.cpp.s

# Object files for target saper
saper_OBJECTS = \
"CMakeFiles/saper.dir/src/main.cpp.o"

# External object files for target saper
saper_EXTERNAL_OBJECTS =

saper: CMakeFiles/saper.dir/src/main.cpp.o
saper: CMakeFiles/saper.dir/build.make
saper: libsaper-lib.a
saper: libsaper-lib.a
saper: /home/szymon/SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
saper: /home/szymon/SFML-2.5.1/lib/libsfml-window.so.2.5.1
saper: /home/szymon/SFML-2.5.1/lib/libsfml-system.so.2.5.1
saper: CMakeFiles/saper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/szymon/CppProjects/saper/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable saper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/saper.dir/build: saper

.PHONY : CMakeFiles/saper.dir/build

CMakeFiles/saper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/saper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/saper.dir/clean

CMakeFiles/saper.dir/depend:
	cd /home/szymon/CppProjects/saper/build/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/szymon/CppProjects/saper /home/szymon/CppProjects/saper /home/szymon/CppProjects/saper/build/Debug /home/szymon/CppProjects/saper/build/Debug /home/szymon/CppProjects/saper/build/Debug/CMakeFiles/saper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/saper.dir/depend
