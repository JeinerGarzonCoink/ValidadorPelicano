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
CMAKE_SOURCE_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build

# Include any dependencies generated for this target.
include CMakeFiles/Unitest_SimplePoll.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Unitest_SimplePoll.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Unitest_SimplePoll.dir/flags.make

CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o: CMakeFiles/Unitest_SimplePoll.dir/flags.make
CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o: ../Unitest_SimplePoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o -c /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/Unitest_SimplePoll.cpp

CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/Unitest_SimplePoll.cpp > CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.i

CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/Unitest_SimplePoll.cpp -o CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.s

# Object files for target Unitest_SimplePoll
Unitest_SimplePoll_OBJECTS = \
"CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o"

# External object files for target Unitest_SimplePoll
Unitest_SimplePoll_EXTERNAL_OBJECTS = \
"/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/ValidatorPelicano.o"

Unitest_SimplePoll: CMakeFiles/Unitest_SimplePoll.dir/Unitest_SimplePoll.cpp.o
Unitest_SimplePoll: ../ValidatorPelicano.o
Unitest_SimplePoll: CMakeFiles/Unitest_SimplePoll.dir/build.make
Unitest_SimplePoll: lib/libgtest_main.a
Unitest_SimplePoll: lib/libgtest.a
Unitest_SimplePoll: CMakeFiles/Unitest_SimplePoll.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Unitest_SimplePoll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unitest_SimplePoll.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=Unitest_SimplePoll -D TEST_EXECUTABLE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build/Unitest_SimplePoll -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=Unitest_SimplePoll_TESTS -D CTEST_FILE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build/Unitest_SimplePoll[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.18/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/Unitest_SimplePoll.dir/build: Unitest_SimplePoll

.PHONY : CMakeFiles/Unitest_SimplePoll.dir/build

CMakeFiles/Unitest_SimplePoll.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Unitest_SimplePoll.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Unitest_SimplePoll.dir/clean

CMakeFiles/Unitest_SimplePoll.dir/depend:
	cd /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_SimplePoll/build/CMakeFiles/Unitest_SimplePoll.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Unitest_SimplePoll.dir/depend

