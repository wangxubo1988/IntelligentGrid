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
include src/reportdata/CMakeFiles/reportdata.dir/depend.make

# Include the progress variables for this target.
include src/reportdata/CMakeFiles/reportdata.dir/progress.make

# Include the compile flags for this target's objects.
include src/reportdata/CMakeFiles/reportdata.dir/flags.make

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o: src/reportdata/CMakeFiles/reportdata.dir/flags.make
src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o: ../src/reportdata/reportdata.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/reportdata.dir/reportdata.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/reportdata/reportdata.c

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reportdata.dir/reportdata.c.i"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/reportdata/reportdata.c > CMakeFiles/reportdata.dir/reportdata.c.i

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reportdata.dir/reportdata.c.s"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/reportdata/reportdata.c -o CMakeFiles/reportdata.dir/reportdata.c.s

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.requires:
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.requires

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.provides: src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.requires
	$(MAKE) -f src/reportdata/CMakeFiles/reportdata.dir/build.make src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.provides.build
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.provides

src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.provides.build: src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o

# Object files for target reportdata
reportdata_OBJECTS = \
"CMakeFiles/reportdata.dir/reportdata.c.o"

# External object files for target reportdata
reportdata_EXTERNAL_OBJECTS =

src/reportdata/libreportdata.a: src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o
src/reportdata/libreportdata.a: src/reportdata/CMakeFiles/reportdata.dir/build.make
src/reportdata/libreportdata.a: src/reportdata/CMakeFiles/reportdata.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libreportdata.a"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && $(CMAKE_COMMAND) -P CMakeFiles/reportdata.dir/cmake_clean_target.cmake
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reportdata.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/reportdata/CMakeFiles/reportdata.dir/build: src/reportdata/libreportdata.a
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/build

src/reportdata/CMakeFiles/reportdata.dir/requires: src/reportdata/CMakeFiles/reportdata.dir/reportdata.c.o.requires
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/requires

src/reportdata/CMakeFiles/reportdata.dir/clean:
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata && $(CMAKE_COMMAND) -P CMakeFiles/reportdata.dir/cmake_clean.cmake
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/clean

src/reportdata/CMakeFiles/reportdata.dir/depend:
	cd /home/work/wxb/gwfile/IntelligentGrid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/work/wxb/gwfile/IntelligentGrid /home/work/wxb/gwfile/IntelligentGrid/src/reportdata /home/work/wxb/gwfile/IntelligentGrid/build /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata /home/work/wxb/gwfile/IntelligentGrid/build/src/reportdata/CMakeFiles/reportdata.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/reportdata/CMakeFiles/reportdata.dir/depend

