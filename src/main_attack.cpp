#include <iostream>
#include <string>
#include <cstdlib>
#include <libsumo/libtraci.h>
#include <libsumo/TrafficLight.h>
#include <libsumo/Vehicle.h>
#include <vector>
#include <exception>
#include <fstream>
#include "traffic_light_diy.h"
#include "vehicle_diy.h"
#include "phase_diy.h"
#include "arrival_table_diy.h"
#include "time_schedule.h"
#include "attacker.h"

using namespace libtraci;
using namespace LIBSUMO_NAMESPACE;
using namespace std;

int main(int argc, char* argv[]) {
	string tl_id = "center";
	bool is_initialize = true;
	vector<PhaseDIY> phases;
	vector<VehicleDIY> vehicles;
	double geofence = 300.0;
	int time_period = 130;
	int last_delta = 0;
	int cop_time;
	int cur_time = 0;
	int max_delay = 0;
	int base_line;
	int whole_time;
	Attacker attacker(true, 119, 1);
	libsumo::TraCILogic logic;
	pair<int, vector<libsumo::TraCIPhase*>> cop_ctrl;

	TimeSchedule scheduler(ITERATOR);
	scheduler.set_tl_id(tl_id);
	Simulation::start({"sumo-gui", "-c", "congestion.sumocfg", "--quit-on-end", "--delay", "20"});
	is_initialize = true;
	while(Simulation::getMinExpectedNumber() > 0) {
		Simulation::step();
		cur_time = Simulation::getCurrentTime() / 1000;
		if(Simulation::isLoaded()) {
			// cout << "state: " << TrafficLight::getRedYellowGreenState(tl_id) << endl;
			if(is_initialize) {
				// fetch initial traffic light states
				phases = PhaseDIY::init_phases(tl_id, cop_time, logic);
				is_initialize = false;
				last_delta = cop_time;
			}

			if(cur_time >= cop_time) {
				vehicles = VehicleDIY::get_all_vehicles();
				ArrivalTableDIY at(geofence, time_period, phases, vehicles);
				TrafficLightDIY tl(tl_id, at, logic, attacker);
				cop_ctrl = tl.update_signal_plan(phases);
				if(cop_ctrl.first > 0) {
					cop_time += cop_ctrl.first;
					last_delta = cop_ctrl.first;
					scheduler.update_phases(cur_time, cop_ctrl.second);
				} else {
					cop_time += last_delta;
					scheduler.set_start_time(cur_time);
				}
			}
			scheduler.update(cur_time);
		}
	}
	Simulation::close();

	return 0;
}
