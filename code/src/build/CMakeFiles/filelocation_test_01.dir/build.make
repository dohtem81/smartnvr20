# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /usr/smartnvr20/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/smartnvr20/src/build

# Include any dependencies generated for this target.
include CMakeFiles/filelocation_test_01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/filelocation_test_01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/filelocation_test_01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/filelocation_test_01.dir/flags.make

CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o: CMakeFiles/filelocation_test_01.dir/flags.make
CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o: /usr/smartnvr20/src/tests/lib/filelocation_test_01.cpp
CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o: CMakeFiles/filelocation_test_01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/smartnvr20/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o -MF CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o.d -o CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o -c /usr/smartnvr20/src/tests/lib/filelocation_test_01.cpp

CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.i"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/smartnvr20/src/tests/lib/filelocation_test_01.cpp > CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.i

CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.s"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/smartnvr20/src/tests/lib/filelocation_test_01.cpp -o CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.s

# Object files for target filelocation_test_01
filelocation_test_01_OBJECTS = \
"CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o"

# External object files for target filelocation_test_01
filelocation_test_01_EXTERNAL_OBJECTS =

tests/filelocation_test_01: CMakeFiles/filelocation_test_01.dir/tests/lib/filelocation_test_01.cpp.o
tests/filelocation_test_01: CMakeFiles/filelocation_test_01.dir/build.make
tests/filelocation_test_01: /usr/local/lib/libopencv_gapi.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_highgui.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_ml.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_objdetect.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_photo.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_stitching.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_video.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_videoio.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libhiredis.so.1.2.1-dev
tests/filelocation_test_01: /usr/local/lib/libopencv_imgcodecs.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_dnn.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_calib3d.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_features2d.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_flann.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_imgproc.so.4.9.0
tests/filelocation_test_01: /usr/local/lib/libopencv_core.so.4.9.0
tests/filelocation_test_01: CMakeFiles/filelocation_test_01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/smartnvr20/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests/filelocation_test_01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/filelocation_test_01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/filelocation_test_01.dir/build: tests/filelocation_test_01
.PHONY : CMakeFiles/filelocation_test_01.dir/build

CMakeFiles/filelocation_test_01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/filelocation_test_01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/filelocation_test_01.dir/clean

CMakeFiles/filelocation_test_01.dir/depend:
	cd /usr/smartnvr20/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/smartnvr20/src /usr/smartnvr20/src /usr/smartnvr20/src/build /usr/smartnvr20/src/build /usr/smartnvr20/src/build/CMakeFiles/filelocation_test_01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/filelocation_test_01.dir/depend

