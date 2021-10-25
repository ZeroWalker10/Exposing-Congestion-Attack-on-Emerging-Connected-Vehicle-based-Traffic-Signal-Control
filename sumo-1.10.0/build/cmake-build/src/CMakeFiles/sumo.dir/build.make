# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/zero/dev/paper/congestion_attack/sumo-1.10.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build

# Include any dependencies generated for this target.
include src/CMakeFiles/sumo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/sumo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/sumo.dir/flags.make

src/CMakeFiles/sumo.dir/sumo_main.cpp.o: src/CMakeFiles/sumo.dir/flags.make
src/CMakeFiles/sumo.dir/sumo_main.cpp.o: ../../src/sumo_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/sumo.dir/sumo_main.cpp.o"
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sumo.dir/sumo_main.cpp.o -c /home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/sumo_main.cpp

src/CMakeFiles/sumo.dir/sumo_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sumo.dir/sumo_main.cpp.i"
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/sumo_main.cpp > CMakeFiles/sumo.dir/sumo_main.cpp.i

src/CMakeFiles/sumo.dir/sumo_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sumo.dir/sumo_main.cpp.s"
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/sumo_main.cpp -o CMakeFiles/sumo.dir/sumo_main.cpp.s

# Object files for target sumo
sumo_OBJECTS = \
"CMakeFiles/sumo.dir/sumo_main.cpp.o"

# External object files for target sumo
sumo_EXTERNAL_OBJECTS =

../../bin/sumo: src/CMakeFiles/sumo.dir/sumo_main.cpp.o
../../bin/sumo: src/CMakeFiles/sumo.dir/build.make
../../bin/sumo: src/microsim/libmicrosim.a
../../bin/sumo: src/traci-server/libtraciserver.a
../../bin/sumo: src/libsumo/liblibsumostatic.a
../../bin/sumo: src/traci-server/libtraciserver.a
../../bin/sumo: src/netload/libnetload.a
../../bin/sumo: src/microsim/cfmodels/libmicrosim_cfmodels.a
../../bin/sumo: src/microsim/engine/libmicrosim_engine.a
../../bin/sumo: src/microsim/lcmodels/libmicrosim_lcmodels.a
../../bin/sumo: src/microsim/devices/libmicrosim_devices.a
../../bin/sumo: src/microsim/trigger/libmicrosim_trigger.a
../../bin/sumo: src/microsim/output/libmicrosim_output.a
../../bin/sumo: src/microsim/transportables/libmicrosim_transportables.a
../../bin/sumo: src/microsim/actions/libmicrosim_actions.a
../../bin/sumo: src/microsim/traffic_lights/libmicrosim_traffic_lights.a
../../bin/sumo: src/microsim/libmicrosim.a
../../bin/sumo: src/mesosim/libmesosim.a
../../bin/sumo: src/utils/emissions/libutils_emissions.a
../../bin/sumo: src/foreign/PHEMlight/cpp/libforeign_phemlight.a
../../bin/sumo: src/utils/vehicle/libutils_vehicle.a
../../bin/sumo: src/utils/distribution/libutils_distribution.a
../../bin/sumo: src/utils/handlers/libutils_handlers.a
../../bin/sumo: src/utils/shapes/libutils_shapes.a
../../bin/sumo: src/utils/options/libutils_options.a
../../bin/sumo: src/utils/xml/libutils_xml.a
../../bin/sumo: src/utils/geom/libutils_geom.a
../../bin/sumo: src/utils/common/libutils_common.a
../../bin/sumo: src/utils/importio/libutils_importio.a
../../bin/sumo: src/utils/iodevices/libutils_iodevices.a
../../bin/sumo: src/utils/traction_wire/libutils_traction_wire.a
../../bin/sumo: src/foreign/tcpip/libforeign_tcpip.a
../../bin/sumo: /usr/lib/x86_64-linux-gnu/libxerces-c.so
../../bin/sumo: /usr/lib/x86_64-linux-gnu/libz.so
../../bin/sumo: /usr/lib/x86_64-linux-gnu/libproj.so
../../bin/sumo: src/CMakeFiles/sumo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/sumo"
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sumo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/sumo.dir/build: ../../bin/sumo

.PHONY : src/CMakeFiles/sumo.dir/build

src/CMakeFiles/sumo.dir/clean:
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src && $(CMAKE_COMMAND) -P CMakeFiles/sumo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/sumo.dir/clean

src/CMakeFiles/sumo.dir/depend:
	cd /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zero/dev/paper/congestion_attack/sumo-1.10.0 /home/zero/dev/paper/congestion_attack/sumo-1.10.0/src /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src/CMakeFiles/sumo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/sumo.dir/depend

