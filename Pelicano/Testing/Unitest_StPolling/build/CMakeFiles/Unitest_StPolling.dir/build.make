# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build

# Include any dependencies generated for this target.
include CMakeFiles/Unitest_StPolling.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Unitest_StPolling.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Unitest_StPolling.dir/flags.make

CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o: CMakeFiles/Unitest_StPolling.dir/flags.make
CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o: ../Unitest_StPolling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o -c /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/Unitest_StPolling.cpp

CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/Unitest_StPolling.cpp > CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.i

CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/Unitest_StPolling.cpp -o CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.s

# Object files for target Unitest_StPolling
Unitest_StPolling_OBJECTS = \
"CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o"

# External object files for target Unitest_StPolling
Unitest_StPolling_EXTERNAL_OBJECTS = \
"/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/ValidatorPelicano.o"

Unitest_StPolling: CMakeFiles/Unitest_StPolling.dir/Unitest_StPolling.cpp.o
Unitest_StPolling: ../ValidatorPelicano.o
Unitest_StPolling: CMakeFiles/Unitest_StPolling.dir/build.make
Unitest_StPolling: lib/libgtest_main.a
Unitest_StPolling: lib/libgtest.a
Unitest_StPolling: CMakeFiles/Unitest_StPolling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Unitest_StPolling"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unitest_StPolling.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=Unitest_StPolling -D TEST_EXECUTABLE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build/Unitest_StPolling -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=Unitest_StPolling_TESTS -D CTEST_FILE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build/Unitest_StPolling[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.18/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/Unitest_StPolling.dir/build: Unitest_StPolling

.PHONY : CMakeFiles/Unitest_StPolling.dir/build

CMakeFiles/Unitest_StPolling.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Unitest_StPolling.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Unitest_StPolling.dir/clean

CMakeFiles/Unitest_StPolling.dir/depend:
	cd /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StPolling/build/CMakeFiles/Unitest_StPolling.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Unitest_StPolling.dir/depend

