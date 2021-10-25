# CMake generated Testfile for 
# Source directory: /home/zero/dev/paper/congestion_attack/sumo-1.10.0
# Build directory: /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(exampletest "/usr/bin/python3.8" "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/docs/examples/runAll.py")
set_tests_properties(exampletest PROPERTIES  _BACKTRACE_TRIPLES "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/CMakeLists.txt;686;add_test;/home/zero/dev/paper/congestion_attack/sumo-1.10.0/CMakeLists.txt;0;")
subdirs("src")
