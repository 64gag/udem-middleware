# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build"

# Include any dependencies generated for this target.
include src/CMakeFiles/Master.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Master.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Master.dir/flags.make

src/CMakeFiles/Master.dir/Master.cpp.o: src/CMakeFiles/Master.dir/flags.make
src/CMakeFiles/Master.dir/Master.cpp.o: ../src/Master.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Master.dir/Master.cpp.o"
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Master.dir/Master.cpp.o -c "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/src/Master.cpp"

src/CMakeFiles/Master.dir/Master.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Master.dir/Master.cpp.i"
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/src/Master.cpp" > CMakeFiles/Master.dir/Master.cpp.i

src/CMakeFiles/Master.dir/Master.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Master.dir/Master.cpp.s"
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/src/Master.cpp" -o CMakeFiles/Master.dir/Master.cpp.s

src/CMakeFiles/Master.dir/Master.cpp.o.requires:
.PHONY : src/CMakeFiles/Master.dir/Master.cpp.o.requires

src/CMakeFiles/Master.dir/Master.cpp.o.provides: src/CMakeFiles/Master.dir/Master.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/Master.dir/build.make src/CMakeFiles/Master.dir/Master.cpp.o.provides.build
.PHONY : src/CMakeFiles/Master.dir/Master.cpp.o.provides

src/CMakeFiles/Master.dir/Master.cpp.o.provides.build: src/CMakeFiles/Master.dir/Master.cpp.o

# Object files for target Master
Master_OBJECTS = \
"CMakeFiles/Master.dir/Master.cpp.o"

# External object files for target Master
Master_EXTERNAL_OBJECTS =

src/Master.so: src/CMakeFiles/Master.dir/Master.cpp.o
src/Master.so: src/CMakeFiles/Master.dir/build.make
src/Master.so: src/CMakeFiles/Master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library Master.so"
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Master.dir/build: src/Master.so
.PHONY : src/CMakeFiles/Master.dir/build

src/CMakeFiles/Master.dir/requires: src/CMakeFiles/Master.dir/Master.cpp.o.requires
.PHONY : src/CMakeFiles/Master.dir/requires

src/CMakeFiles/Master.dir/clean:
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/Master.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Master.dir/clean

src/CMakeFiles/Master.dir/depend:
	cd "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master" "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/src" "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build" "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src" "/home/paguiar/Dropbox/UDEM/PPD - Middleware/eclipse/master/build/src/CMakeFiles/Master.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/Master.dir/depend

