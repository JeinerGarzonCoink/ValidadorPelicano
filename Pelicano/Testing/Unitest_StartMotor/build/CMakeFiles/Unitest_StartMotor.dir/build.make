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
CMAKE_SOURCE_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build

# Include any dependencies generated for this target.
include CMakeFiles/Unitest_StartMotor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Unitest_StartMotor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Unitest_StartMotor.dir/flags.make

CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o: CMakeFiles/Unitest_StartMotor.dir/flags.make
CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o: ../Unitest_StartMotor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o -c /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/Unitest_StartMotor.cpp

CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/Unitest_StartMotor.cpp > CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.i

CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/Unitest_StartMotor.cpp -o CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.s

# Object files for target Unitest_StartMotor
Unitest_StartMotor_OBJECTS = \
"CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o"

# External object files for target Unitest_StartMotor
Unitest_StartMotor_EXTERNAL_OBJECTS = \
"/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/ValidatorPelicano.o"

Unitest_StartMotor: CMakeFiles/Unitest_StartMotor.dir/Unitest_StartMotor.cpp.o
Unitest_StartMotor: ../ValidatorPelicano.o
Unitest_StartMotor: CMakeFiles/Unitest_StartMotor.dir/build.make
Unitest_StartMotor: lib/libgtest_main.a
Unitest_StartMotor: lib/libgtest.a
Unitest_StartMotor: CMakeFiles/Unitest_StartMotor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Unitest_StartMotor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unitest_StartMotor.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=Unitest_StartMotor -D TEST_EXECUTABLE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build/Unitest_StartMotor -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=Unitest_StartMotor_TESTS -D CTEST_FILE=/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build/Unitest_StartMotor[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.18/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/Unitest_StartMotor.dir/build: Unitest_StartMotor

.PHONY : CMakeFiles/Unitest_StartMotor.dir/build

CMakeFiles/Unitest_StartMotor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Unitest_StartMotor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Unitest_StartMotor.dir/clean

CMakeFiles/Unitest_StartMotor.dir/depend:
	cd /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build /home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/Testing/Unitest_StartMotor/build/CMakeFiles/Unitest_StartMotor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Unitest_StartMotor.dir/depend

