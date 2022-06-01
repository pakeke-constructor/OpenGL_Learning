# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /csse/users/oga20/cosc363/assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /csse/users/oga20/cosc363/assignment

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /csse/users/oga20/cosc363/assignment/CMakeFiles /csse/users/oga20/cosc363/assignment/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /csse/users/oga20/cosc363/assignment/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named assignment.out

# Build rule for target.
assignment.out: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 assignment.out
.PHONY : assignment.out

# fast build rule for target.
assignment.out/fast:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/build
.PHONY : assignment.out/fast

Assignment.o: Assignment.cpp.o

.PHONY : Assignment.o

# target to build an object file
Assignment.cpp.o:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Assignment.cpp.o
.PHONY : Assignment.cpp.o

Assignment.i: Assignment.cpp.i

.PHONY : Assignment.i

# target to preprocess a source file
Assignment.cpp.i:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Assignment.cpp.i
.PHONY : Assignment.cpp.i

Assignment.s: Assignment.cpp.s

.PHONY : Assignment.s

# target to generate assembly for a file
Assignment.cpp.s:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Assignment.cpp.s
.PHONY : Assignment.cpp.s

Rendering.o: Rendering.cpp.o

.PHONY : Rendering.o

# target to build an object file
Rendering.cpp.o:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Rendering.cpp.o
.PHONY : Rendering.cpp.o

Rendering.i: Rendering.cpp.i

.PHONY : Rendering.i

# target to preprocess a source file
Rendering.cpp.i:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Rendering.cpp.i
.PHONY : Rendering.cpp.i

Rendering.s: Rendering.cpp.s

.PHONY : Rendering.s

# target to generate assembly for a file
Rendering.cpp.s:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/Rendering.cpp.s
.PHONY : Rendering.cpp.s

loadBMP.o: loadBMP.cpp.o

.PHONY : loadBMP.o

# target to build an object file
loadBMP.cpp.o:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/loadBMP.cpp.o
.PHONY : loadBMP.cpp.o

loadBMP.i: loadBMP.cpp.i

.PHONY : loadBMP.i

# target to preprocess a source file
loadBMP.cpp.i:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/loadBMP.cpp.i
.PHONY : loadBMP.cpp.i

loadBMP.s: loadBMP.cpp.s

.PHONY : loadBMP.s

# target to generate assembly for a file
loadBMP.cpp.s:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/loadBMP.cpp.s
.PHONY : loadBMP.cpp.s

vecmath.o: vecmath.cpp.o

.PHONY : vecmath.o

# target to build an object file
vecmath.cpp.o:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/vecmath.cpp.o
.PHONY : vecmath.cpp.o

vecmath.i: vecmath.cpp.i

.PHONY : vecmath.i

# target to preprocess a source file
vecmath.cpp.i:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/vecmath.cpp.i
.PHONY : vecmath.cpp.i

vecmath.s: vecmath.cpp.s

.PHONY : vecmath.s

# target to generate assembly for a file
vecmath.cpp.s:
	$(MAKE) -f CMakeFiles/assignment.out.dir/build.make CMakeFiles/assignment.out.dir/vecmath.cpp.s
.PHONY : vecmath.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... assignment.out"
	@echo "... Assignment.o"
	@echo "... Assignment.i"
	@echo "... Assignment.s"
	@echo "... Rendering.o"
	@echo "... Rendering.i"
	@echo "... Rendering.s"
	@echo "... loadBMP.o"
	@echo "... loadBMP.i"
	@echo "... loadBMP.s"
	@echo "... vecmath.o"
	@echo "... vecmath.i"
	@echo "... vecmath.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
