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
CMAKE_SOURCE_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build

# Include any dependencies generated for this target.
include CMakeFiles/UnitTest_StConnect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UnitTest_StConnect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UnitTest_StConnect.dir/flags.make

CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o: CMakeFiles/UnitTest_StConnect.dir/flags.make
CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o: ../UnitTest_StConnect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o -c /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/UnitTest_StConnect.cpp

CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/UnitTest_StConnect.cpp > CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.i

CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/UnitTest_StConnect.cpp -o CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.s

# Object files for target UnitTest_StConnect
UnitTest_StConnect_OBJECTS = \
"CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o"

# External object files for target UnitTest_StConnect
UnitTest_StConnect_EXTERNAL_OBJECTS = \
"/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/ValidatorPelicano.o"

UnitTest_StConnect: CMakeFiles/UnitTest_StConnect.dir/UnitTest_StConnect.cpp.o
UnitTest_StConnect: ../ValidatorPelicano.o
UnitTest_StConnect: CMakeFiles/UnitTest_StConnect.dir/build.make
UnitTest_StConnect: lib/libgtest_main.a
UnitTest_StConnect: lib/libgtest.a
UnitTest_StConnect: CMakeFiles/UnitTest_StConnect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable UnitTest_StConnect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UnitTest_StConnect.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=UnitTest_StConnect -D TEST_EXECUTABLE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build/UnitTest_StConnect -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=UnitTest_StConnect_TESTS -D CTEST_FILE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build/UnitTest_StConnect[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.18/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/UnitTest_StConnect.dir/build: UnitTest_StConnect

.PHONY : CMakeFiles/UnitTest_StConnect.dir/build

CMakeFiles/UnitTest_StConnect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UnitTest_StConnect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UnitTest_StConnect.dir/clean

CMakeFiles/UnitTest_StConnect.dir/depend:
	cd /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StConnect/build/CMakeFiles/UnitTest_StConnect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UnitTest_StConnect.dir/depend

