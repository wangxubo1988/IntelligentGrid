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
include CMakeFiles/IntelligentGrid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IntelligentGrid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IntelligentGrid.dir/flags.make

CMakeFiles/IntelligentGrid.dir/src/app/main.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/main.c.o: ../src/app/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/main.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/main.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/main.c

CMakeFiles/IntelligentGrid.dir/src/app/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/main.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/main.c > CMakeFiles/IntelligentGrid.dir/src/app/main.c.i

CMakeFiles/IntelligentGrid.dir/src/app/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/main.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/main.c -o CMakeFiles/IntelligentGrid.dir/src/app/main.c.s

CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/main.c.o

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o: ../src/app/MyThread.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/MyThread.c

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/MyThread.c > CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.i

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/MyThread.c -o CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.s

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o: ../src/app/SystemInit.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/SystemInit.c

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/SystemInit.c > CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.i

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/SystemInit.c -o CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.s

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o: ../src/app/DataCollection.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/DataCollection.c

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/DataCollection.c > CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.i

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/DataCollection.c -o CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.s

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o: ../src/app/Data_handle.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/Data_handle.c

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/Data_handle.c > CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.i

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/Data_handle.c -o CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.s

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o: CMakeFiles/IntelligentGrid.dir/flags.make
CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o: ../src/app/tag_manage.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o   -c /home/work/wxb/gwfile/IntelligentGrid/src/app/tag_manage.c

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.i"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/wxb/gwfile/IntelligentGrid/src/app/tag_manage.c > CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.i

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.s"
	/opt/EmbedSky/4.3.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/wxb/gwfile/IntelligentGrid/src/app/tag_manage.c -o CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.s

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.requires:
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.requires

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.provides: CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.requires
	$(MAKE) -f CMakeFiles/IntelligentGrid.dir/build.make CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.provides.build
.PHONY : CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.provides

CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.provides.build: CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o

# Object files for target IntelligentGrid
IntelligentGrid_OBJECTS = \
"CMakeFiles/IntelligentGrid.dir/src/app/main.c.o" \
"CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o" \
"CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o" \
"CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o" \
"CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o" \
"CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o"

# External object files for target IntelligentGrid
IntelligentGrid_EXTERNAL_OBJECTS =

../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/main.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/build.make
../bin/IntelligentGrid: src/reportdata/libreportdata.a
../bin/IntelligentGrid: src/DataPKG/libDataPKG.a
../bin/IntelligentGrid: ../libs/lib/libxml2.so
../bin/IntelligentGrid: src/xmlparse/libxmlparse.a
../bin/IntelligentGrid: src/uart/libuart.a
../bin/IntelligentGrid: src/DeviceMgmt/libDeviceMgmt.a
../bin/IntelligentGrid: src/datastore/libdatastore.a
../bin/IntelligentGrid: src/mysqlite/libmysqlite.a
../bin/IntelligentGrid: src/mylog/libmylog.a
../bin/IntelligentGrid: ../libs/lib/liblog4c.so
../bin/IntelligentGrid: ../libs/lib/libsqlite3.so
../bin/IntelligentGrid: ../libs/lib/libmpr.so
../bin/IntelligentGrid: src/IEC103/libIEC103.a
../bin/IntelligentGrid: src/watchdog/libwatchdog.a
../bin/IntelligentGrid: src/mysocket/libmysocket.a
../bin/IntelligentGrid: src/FuncPKG/libFuncPKG.a
../bin/IntelligentGrid: CMakeFiles/IntelligentGrid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/IntelligentGrid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IntelligentGrid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IntelligentGrid.dir/build: ../bin/IntelligentGrid
.PHONY : CMakeFiles/IntelligentGrid.dir/build

CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/main.c.o.requires
CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/MyThread.c.o.requires
CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/SystemInit.c.o.requires
CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/DataCollection.c.o.requires
CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/Data_handle.c.o.requires
CMakeFiles/IntelligentGrid.dir/requires: CMakeFiles/IntelligentGrid.dir/src/app/tag_manage.c.o.requires
.PHONY : CMakeFiles/IntelligentGrid.dir/requires

CMakeFiles/IntelligentGrid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IntelligentGrid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IntelligentGrid.dir/clean

CMakeFiles/IntelligentGrid.dir/depend:
	cd /home/work/wxb/gwfile/IntelligentGrid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/work/wxb/gwfile/IntelligentGrid /home/work/wxb/gwfile/IntelligentGrid /home/work/wxb/gwfile/IntelligentGrid/build /home/work/wxb/gwfile/IntelligentGrid/build /home/work/wxb/gwfile/IntelligentGrid/build/CMakeFiles/IntelligentGrid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IntelligentGrid.dir/depend
