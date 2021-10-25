# CMake generated Testfile for 
# Source directory: /home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/traci_testclient
# Build directory: /home/zero/dev/paper/congestion_attack/sumo-1.10.0/build/cmake-build/src/traci_testclient
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(libsumotest "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/bin/testlibsumo")
set_tests_properties(libsumotest PROPERTIES  _BACKTRACE_TRIPLES "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/traci_testclient/CMakeLists.txt;18;add_test;/home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/traci_testclient/CMakeLists.txt;0;")
add_test(libsumostatictest "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/bin/testlibsumostatic")
set_tests_properties(libsumostatictest PROPERTIES  _BACKTRACE_TRIPLES "/home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/traci_testclient/CMakeLists.txt;23;add_test;/home/zero/dev/paper/congestion_attack/sumo-1.10.0/src/traci_testclient/CMakeLists.txt;0;")
