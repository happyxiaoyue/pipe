# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/chenhao/wrkprj/pipe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chenhao/wrkprj/pipe/build

# Include any dependencies generated for this target.
include CMakeFiles/pipe_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pipe_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pipe_test.dir/flags.make

CMakeFiles/pipe_test.dir/main.c.o: CMakeFiles/pipe_test.dir/flags.make
CMakeFiles/pipe_test.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenhao/wrkprj/pipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pipe_test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pipe_test.dir/main.c.o   -c /home/chenhao/wrkprj/pipe/main.c

CMakeFiles/pipe_test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pipe_test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chenhao/wrkprj/pipe/main.c > CMakeFiles/pipe_test.dir/main.c.i

CMakeFiles/pipe_test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pipe_test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chenhao/wrkprj/pipe/main.c -o CMakeFiles/pipe_test.dir/main.c.s

CMakeFiles/pipe_test.dir/main.c.o.requires:

.PHONY : CMakeFiles/pipe_test.dir/main.c.o.requires

CMakeFiles/pipe_test.dir/main.c.o.provides: CMakeFiles/pipe_test.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/pipe_test.dir/build.make CMakeFiles/pipe_test.dir/main.c.o.provides.build
.PHONY : CMakeFiles/pipe_test.dir/main.c.o.provides

CMakeFiles/pipe_test.dir/main.c.o.provides.build: CMakeFiles/pipe_test.dir/main.c.o


CMakeFiles/pipe_test.dir/pipe.c.o: CMakeFiles/pipe_test.dir/flags.make
CMakeFiles/pipe_test.dir/pipe.c.o: ../pipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenhao/wrkprj/pipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/pipe_test.dir/pipe.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pipe_test.dir/pipe.c.o   -c /home/chenhao/wrkprj/pipe/pipe.c

CMakeFiles/pipe_test.dir/pipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pipe_test.dir/pipe.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chenhao/wrkprj/pipe/pipe.c > CMakeFiles/pipe_test.dir/pipe.c.i

CMakeFiles/pipe_test.dir/pipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pipe_test.dir/pipe.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chenhao/wrkprj/pipe/pipe.c -o CMakeFiles/pipe_test.dir/pipe.c.s

CMakeFiles/pipe_test.dir/pipe.c.o.requires:

.PHONY : CMakeFiles/pipe_test.dir/pipe.c.o.requires

CMakeFiles/pipe_test.dir/pipe.c.o.provides: CMakeFiles/pipe_test.dir/pipe.c.o.requires
	$(MAKE) -f CMakeFiles/pipe_test.dir/build.make CMakeFiles/pipe_test.dir/pipe.c.o.provides.build
.PHONY : CMakeFiles/pipe_test.dir/pipe.c.o.provides

CMakeFiles/pipe_test.dir/pipe.c.o.provides.build: CMakeFiles/pipe_test.dir/pipe.c.o


CMakeFiles/pipe_test.dir/pipe_util.c.o: CMakeFiles/pipe_test.dir/flags.make
CMakeFiles/pipe_test.dir/pipe_util.c.o: ../pipe_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenhao/wrkprj/pipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/pipe_test.dir/pipe_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pipe_test.dir/pipe_util.c.o   -c /home/chenhao/wrkprj/pipe/pipe_util.c

CMakeFiles/pipe_test.dir/pipe_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pipe_test.dir/pipe_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chenhao/wrkprj/pipe/pipe_util.c > CMakeFiles/pipe_test.dir/pipe_util.c.i

CMakeFiles/pipe_test.dir/pipe_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pipe_test.dir/pipe_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chenhao/wrkprj/pipe/pipe_util.c -o CMakeFiles/pipe_test.dir/pipe_util.c.s

CMakeFiles/pipe_test.dir/pipe_util.c.o.requires:

.PHONY : CMakeFiles/pipe_test.dir/pipe_util.c.o.requires

CMakeFiles/pipe_test.dir/pipe_util.c.o.provides: CMakeFiles/pipe_test.dir/pipe_util.c.o.requires
	$(MAKE) -f CMakeFiles/pipe_test.dir/build.make CMakeFiles/pipe_test.dir/pipe_util.c.o.provides.build
.PHONY : CMakeFiles/pipe_test.dir/pipe_util.c.o.provides

CMakeFiles/pipe_test.dir/pipe_util.c.o.provides.build: CMakeFiles/pipe_test.dir/pipe_util.c.o


# Object files for target pipe_test
pipe_test_OBJECTS = \
"CMakeFiles/pipe_test.dir/main.c.o" \
"CMakeFiles/pipe_test.dir/pipe.c.o" \
"CMakeFiles/pipe_test.dir/pipe_util.c.o"

# External object files for target pipe_test
pipe_test_EXTERNAL_OBJECTS =

pipe_test: CMakeFiles/pipe_test.dir/main.c.o
pipe_test: CMakeFiles/pipe_test.dir/pipe.c.o
pipe_test: CMakeFiles/pipe_test.dir/pipe_util.c.o
pipe_test: CMakeFiles/pipe_test.dir/build.make
pipe_test: CMakeFiles/pipe_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chenhao/wrkprj/pipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable pipe_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pipe_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pipe_test.dir/build: pipe_test

.PHONY : CMakeFiles/pipe_test.dir/build

CMakeFiles/pipe_test.dir/requires: CMakeFiles/pipe_test.dir/main.c.o.requires
CMakeFiles/pipe_test.dir/requires: CMakeFiles/pipe_test.dir/pipe.c.o.requires
CMakeFiles/pipe_test.dir/requires: CMakeFiles/pipe_test.dir/pipe_util.c.o.requires

.PHONY : CMakeFiles/pipe_test.dir/requires

CMakeFiles/pipe_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pipe_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pipe_test.dir/clean

CMakeFiles/pipe_test.dir/depend:
	cd /home/chenhao/wrkprj/pipe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chenhao/wrkprj/pipe /home/chenhao/wrkprj/pipe /home/chenhao/wrkprj/pipe/build /home/chenhao/wrkprj/pipe/build /home/chenhao/wrkprj/pipe/build/CMakeFiles/pipe_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pipe_test.dir/depend

