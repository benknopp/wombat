# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bknopp/Workspaces/tracking/wombat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bknopp/Workspaces/tracking/wombat/build

# Include any dependencies generated for this target.
include extern/libPtc/CMakeFiles/Ptc.dir/depend.make

# Include the progress variables for this target.
include extern/libPtc/CMakeFiles/Ptc.dir/progress.make

# Include the compile flags for this target's objects.
include extern/libPtc/CMakeFiles/Ptc.dir/flags.make

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o: extern/libPtc/CMakeFiles/Ptc.dir/flags.make
extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o: ../extern/libPtc/src/Reader.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bknopp/Workspaces/tracking/wombat/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Ptc.dir/src/Reader.cc.o -c /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Reader.cc

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ptc.dir/src/Reader.cc.i"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Reader.cc > CMakeFiles/Ptc.dir/src/Reader.cc.i

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ptc.dir/src/Reader.cc.s"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Reader.cc -o CMakeFiles/Ptc.dir/src/Reader.cc.s

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.requires:
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.requires

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.provides: extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.requires
	$(MAKE) -f extern/libPtc/CMakeFiles/Ptc.dir/build.make extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.provides.build
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.provides

extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.provides.build: extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.provides.build

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o: extern/libPtc/CMakeFiles/Ptc.dir/flags.make
extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o: ../extern/libPtc/src/Writer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bknopp/Workspaces/tracking/wombat/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Ptc.dir/src/Writer.cc.o -c /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Writer.cc

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ptc.dir/src/Writer.cc.i"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Writer.cc > CMakeFiles/Ptc.dir/src/Writer.cc.i

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ptc.dir/src/Writer.cc.s"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bknopp/Workspaces/tracking/wombat/extern/libPtc/src/Writer.cc -o CMakeFiles/Ptc.dir/src/Writer.cc.s

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.requires:
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.requires

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.provides: extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.requires
	$(MAKE) -f extern/libPtc/CMakeFiles/Ptc.dir/build.make extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.provides.build
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.provides

extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.provides.build: extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.provides.build

# Object files for target Ptc
Ptc_OBJECTS = \
"CMakeFiles/Ptc.dir/src/Reader.cc.o" \
"CMakeFiles/Ptc.dir/src/Writer.cc.o"

# External object files for target Ptc
Ptc_EXTERNAL_OBJECTS =

lib/libPtc.so.0.1.0: extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o
lib/libPtc.so.0.1.0: extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o
lib/libPtc.so.0.1.0: /usr/lib64/libGLU.so
lib/libPtc.so.0.1.0: /usr/lib64/libGL.so
lib/libPtc.so.0.1.0: /usr/lib64/libSM.so
lib/libPtc.so.0.1.0: /usr/lib64/libICE.so
lib/libPtc.so.0.1.0: /usr/lib64/libX11.so
lib/libPtc.so.0.1.0: /usr/lib64/libXext.so
lib/libPtc.so.0.1.0: /usr/lib64/libglut.so
lib/libPtc.so.0.1.0: /usr/lib64/libXmu.so
lib/libPtc.so.0.1.0: /usr/lib64/libXi.so
lib/libPtc.so.0.1.0: extern/libPtc/CMakeFiles/Ptc.dir/build.make
lib/libPtc.so.0.1.0: extern/libPtc/CMakeFiles/Ptc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../lib/libPtc.so"
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ptc.dir/link.txt --verbose=$(VERBOSE)
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libPtc.so.0.1.0 ../../lib/libPtc.so.0.1.0 ../../lib/libPtc.so

lib/libPtc.so: lib/libPtc.so.0.1.0

# Rule to build all files generated by this target.
extern/libPtc/CMakeFiles/Ptc.dir/build: lib/libPtc.so
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/build

extern/libPtc/CMakeFiles/Ptc.dir/requires: extern/libPtc/CMakeFiles/Ptc.dir/src/Reader.cc.o.requires
extern/libPtc/CMakeFiles/Ptc.dir/requires: extern/libPtc/CMakeFiles/Ptc.dir/src/Writer.cc.o.requires
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/requires

extern/libPtc/CMakeFiles/Ptc.dir/clean:
	cd /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc && $(CMAKE_COMMAND) -P CMakeFiles/Ptc.dir/cmake_clean.cmake
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/clean

extern/libPtc/CMakeFiles/Ptc.dir/depend:
	cd /home/bknopp/Workspaces/tracking/wombat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bknopp/Workspaces/tracking/wombat /home/bknopp/Workspaces/tracking/wombat/extern/libPtc /home/bknopp/Workspaces/tracking/wombat/build /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc /home/bknopp/Workspaces/tracking/wombat/build/extern/libPtc/CMakeFiles/Ptc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/libPtc/CMakeFiles/Ptc.dir/depend
