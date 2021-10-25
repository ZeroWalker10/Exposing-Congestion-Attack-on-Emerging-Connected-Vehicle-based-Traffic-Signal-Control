CC=g++
CFLAGS=-std=c++11 -g
INC=-I${SUMO_HOME}/src -I./cop -I./include
LIB=-L${SUMO_HOME}/bin
LINK=-ltracicpp -lsumocpp
TARGET=cop_simulate baseline_simulate analysis_simulate attack_simulate
TARGET_OBJ=main_cop.o main_baseline.o main_analysis.o main_attack.o
SRC=traffic_light_diy.cpp arrival_table_diy.cpp vehicle_diy.cpp phase_diy.cpp time_schedule.cpp attacker.cpp
OBJ=$(subst .cpp,.o,$(SRC))

DTARGET=$(patsubst %,build/%,$(TARGET))
DSRC=$(patsubst %,src/%,$(SRC))
DOBJ=$(patsubst %,obj/%,$(OBJ))
DTARGET_OBJ=$(patsubst %,obj/%,$(TARGET_OBJ))

all: $(DTARGET)

build/attack_simulate: obj/main_attack.o $(DOBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^ $(LINK)

build/analysis_simulate: obj/main_analysis.o $(DOBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^ $(LINK)

build/baseline_simulate: obj/main_baseline.o $(DOBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^ $(LINK)

build/cop_simulate: obj/main_cop.o $(DOBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^ $(LINK)

obj/main_cop.o: src/main_cop.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/main_baseline.o: src/main_baseline.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/main_analysis.o: src/main_analysis.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/main_attack.o: src/main_attack.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/traffic_light_diy.o: src/traffic_light_diy.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/vehicle_diy.o: src/vehicle_diy.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/phase_diy.o: src/phase_diy.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/arrival_table_diy.o: src/arrival_table_diy.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/time_schedule.o: src/time_schedule.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

obj/attacker.o: src/attacker.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< $(LINK)

clean:
	rm -f $(DTARGET) $(DOBJ) $(DTARGET_OBJ)
