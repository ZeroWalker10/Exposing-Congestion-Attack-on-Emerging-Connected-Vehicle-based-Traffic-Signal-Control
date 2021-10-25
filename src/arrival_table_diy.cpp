#include <iostream>
#include "arrival_table_diy.h"

using namespace std;

ArrivalTableDIY::ArrivalTableDIY(double geofence, int time_period, const vector<PhaseDIY> &phases, const vector<VehicleDIY> &vehicles)
		: m_geofence(geofence), m_time_period(time_period), m_phases(phases), m_vehicles(vehicles), m_arrival_table(time_period + 1) {
	for(size_t i = 0; i != m_arrival_table.size(); ++i) {
		m_arrival_table[i] = vector<int>(phases.size());
	}

	calculate_arrival_table();
}

void ArrivalTableDIY::calculate_arrival_table() {
	vector<int> last_time(m_phases.size(), 0);
	for(size_t i = 0; i != m_vehicles.size(); ++i) {
		// only consider the vehicle within the geo
		if(m_vehicles[i].get_distance() > m_geofence) {
			continue;
		}

		// only consider the vehicle during the time period
		int time_slot = int(m_vehicles[i].get_expect_arrival_time() + 0.5);
		if(time_slot > m_time_period) {
			continue;
		}

		string cur_edge = m_vehicles[i].get_cur_edge();
		vector<string> route = m_vehicles[i].get_route();
		for(size_t j = 0; j != m_phases.size(); ++j) {
			if(!m_phases[j].is_vehicle_request(route, cur_edge)) {
				continue;
			}

			m_arrival_table[time_slot][m_phases[j].get_id()-1] += 1;
			if(time_slot > last_time[m_phases[j].get_id() - 1]) {
				last_time[m_phases[j].get_id()-1] = time_slot;
			}
		}
	}
}

const vector<vector<int>>& ArrivalTableDIY::get_arrival_table() const {
	return m_arrival_table;
}
