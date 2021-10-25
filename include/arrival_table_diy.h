#ifndef ARRIVAL_TABLE_H
#define ARRIVAL_TABLE_H

#include <vector>
#include "phase_diy.h"
#include "vehicle_diy.h"

class ArrivalTableDIY {
public:
	explicit ArrivalTableDIY(double geofence, int time_period, const std::vector<PhaseDIY> &phases, const std::vector<VehicleDIY> &vehicles);
	const std::vector<std::vector<int>>& get_arrival_table() const;
	void increase_arrival_table(int i, int j, int delta) {
		m_arrival_table[i][j] += delta;
	}
private:
	void calculate_arrival_table();
private:
	double m_geofence;
	int m_time_period;
	std::vector<PhaseDIY> m_phases;
	std::vector<VehicleDIY> m_vehicles;
	std::vector<std::vector<int>> m_arrival_table;
};

#endif
