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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/work/wxb/gwfile/IntelligentGrid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/work/wxb/gwfile/IntelligentGrid/build

# Include any dependencies generated for this target.
include src/IEC103/CMakeFiles/IEC103.dir/depend.make

# Include the progress variables for this target.
include src/IEC103/CMakeFiles/IEC103.dir/progress.make

# Include the compile flags for this target's objects.
include src/IEC103/CMakeFiles/IEC103.dir/flags.make

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o: src/IEC103/CMakeFiles/IEC103.dir/flags.make
src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o: ../src/IEC103/IEC103.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IEC103.dir/IEC103.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/IEC103/IEC103.c

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IEC103.dir/IEC103.c.i"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/IEC103/IEC103.c > CMakeFiles/IEC103.dir/IEC103.c.i

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IEC103.dir/IEC103.c.s"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/IEC103/IEC103.c -o CMakeFiles/IEC103.dir/IEC103.c.s

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.requires:
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.requires

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.provides: src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.requires
	$(MAKE) -f src/IEC103/CMakeFiles/IEC103.dir/build.make src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.provides.build
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.provides

src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.provides.build: src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o

# Object files for target IEC103
IEC103_OBJECTS = \
"CMakeFiles/IEC103.dir/IEC103.c.o"

# External object files for target IEC103
IEC103_EXTERNAL_OBJECTS =

src/IEC103/libIEC103.a: src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o
src/IEC103/libIEC103.a: src/IEC103/CMakeFiles/IEC103.dir/build.make
src/IEC103/libIEC103.a: src/IEC103/CMakeFiles/IEC103.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libIEC103.a"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && $(CMAKE_COMMAND) -P CMakeFiles/IEC103.dir/cmake_clean_target.cmake
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IEC103.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/IEC103/CMakeFiles/IEC103.dir/build: src/IEC103/libIEC103.a
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/build

src/IEC103/CMakeFiles/IEC103.dir/requires: src/IEC103/CMakeFiles/IEC103.dir/IEC103.c.o.requires
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/requires

src/IEC103/CMakeFiles/IEC103.dir/clean:
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 && $(CMAKE_COMMAND) -P CMakeFiles/IEC103.dir/cmake_clean.cmake
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/clean

src/IEC103/CMakeFiles/IEC103.dir/depend:
	cd /home/work/wxb/gwfile/IntelligentGrid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/work/wxb/gwfile/IntelligentGrid /home/work/wxb/gwfile/IntelligentGrid/src/IEC103 /home/work/wxb/gwfile/IntelligentGrid/build /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103 /home/work/wxb/gwfile/IntelligentGrid/build/src/IEC103/CMakeFiles/IEC103.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/IEC103/CMakeFiles/IEC103.dir/depend

