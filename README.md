# Environment
Test on: Ubuntu 20.04

# Environment Variables
SUMO_HOME=<sumo directory>
PATH=\$SUMO_HOME/bin
LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$SUMO_HOME/bin

# Description

- **flow**: generate the vehicle flow, developed with python
- **cop**: COP algorithm, from MMITSS-AZ[^1], developed with C++
- **src**: traffic light schedule and attack logic, developed with C++
- **obj**: compile the source codes in **src** and output the objects into it
- **build**: executable files live there
- **result**: the analysis result 
- **sumo-1.10.0**: simulation software

[^1]: https://github.com/mmitss/mmitss-az

