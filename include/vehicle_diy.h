#ifndef VEHICLE_DIY_H
#define VEHICLE_DIY_H

#include <string>
#include <vector>
#include <iostream>
#include <libsumo/TraCIDefs.h>

class Position {
public:
	double x, y;
};

class VehicleDIY {
public:
	static std::vector<VehicleDIY> get_all_vehicles();
public:
	explicit VehicleDIY(const std::string &id);
	VehicleDIY(const VehicleDIY &veh);
	double get_expect_arrival_time() const;
	std::string get_cur_edge() const;
	std::vector<std::string> get_route() const;
	double get_distance() const;
	void print_vehicle() const;
private:
	std::string m_id;
	double m_speed;			// vehicle speed
	double m_length;		// vehicle length;
	Position m_position;	// vehicle position;
	std::vector<std::string> m_route;		// vehicle route
	std::string m_lane_id;					// current lane
	double m_acceleration;					// vehicle acceleration
	double m_expect_arrival_time;			// estimated arrival_time
	std::string m_type_id;					// vehicle type
};

#endif
