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
include src/xmlparse/CMakeFiles/xmlparse.dir/depend.make

# Include the progress variables for this target.
include src/xmlparse/CMakeFiles/xmlparse.dir/progress.make

# Include the compile flags for this target's objects.
include src/xmlparse/CMakeFiles/xmlparse.dir/flags.make

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o: src/xmlparse/CMakeFiles/xmlparse.dir/flags.make
src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o: ../src/xmlparse/xmlparse.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/xmlparse.dir/xmlparse.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/xmlparse/xmlparse.c

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xmlparse.dir/xmlparse.c.i"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/xmlparse/xmlparse.c > CMakeFiles/xmlparse.dir/xmlparse.c.i

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xmlparse.dir/xmlparse.c.s"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && /opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/xmlparse/xmlparse.c -o CMakeFiles/xmlparse.dir/xmlparse.c.s

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.requires:
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.requires

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.provides: src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.requires
	$(MAKE) -f src/xmlparse/CMakeFiles/xmlparse.dir/build.make src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.provides.build
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.provides

src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.provides.build: src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o

# Object files for target xmlparse
xmlparse_OBJECTS = \
"CMakeFiles/xmlparse.dir/xmlparse.c.o"

# External object files for target xmlparse
xmlparse_EXTERNAL_OBJECTS =

src/xmlparse/libxmlparse.a: src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o
src/xmlparse/libxmlparse.a: src/xmlparse/CMakeFiles/xmlparse.dir/build.make
src/xmlparse/libxmlparse.a: src/xmlparse/CMakeFiles/xmlparse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libxmlparse.a"
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && $(CMAKE_COMMAND) -P CMakeFiles/xmlparse.dir/cmake_clean_target.cmake
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xmlparse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/xmlparse/CMakeFiles/xmlparse.dir/build: src/xmlparse/libxmlparse.a
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/build

src/xmlparse/CMakeFiles/xmlparse.dir/requires: src/xmlparse/CMakeFiles/xmlparse.dir/xmlparse.c.o.requires
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/requires

src/xmlparse/CMakeFiles/xmlparse.dir/clean:
	cd /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse && $(CMAKE_COMMAND) -P CMakeFiles/xmlparse.dir/cmake_clean.cmake
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/clean

src/xmlparse/CMakeFiles/xmlparse.dir/depend:
	cd /home/work/wxb/gwfile/IntelligentGrid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/work/wxb/gwfile/IntelligentGrid /home/work/wxb/gwfile/IntelligentGrid/src/xmlparse /home/work/wxb/gwfile/IntelligentGrid/build /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse /home/work/wxb/gwfile/IntelligentGrid/build/src/xmlparse/CMakeFiles/xmlparse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/xmlparse/CMakeFiles/xmlparse.dir/depend

