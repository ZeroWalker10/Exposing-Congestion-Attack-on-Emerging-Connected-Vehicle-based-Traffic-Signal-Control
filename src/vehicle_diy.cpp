#include <libsumo/libtraci.h>
#include <libsumo/VehicleType.h>
#include <cmath>
#include "vehicle_diy.h"

using namespace libtraci;
using namespace std;

vector<VehicleDIY> VehicleDIY::get_all_vehicles() {
	vector<string> veh_ids = Vehicle::getIDList();
	vector<VehicleDIY> vehs;
	for(size_t i = 0; i != veh_ids.size(); ++i) {
		vehs.push_back(VehicleDIY(veh_ids[i]));
	}

	return vehs;
}

VehicleDIY::VehicleDIY(const std::string &id)
			: m_id(id) {
	m_speed = Vehicle::getSpeed(m_id);
	m_type_id = Vehicle::getTypeID(m_id);
	m_length = Vehicle::getLength(m_id);
	m_route = Vehicle::getRoute(m_id);
	m_lane_id = Vehicle::getLaneID(m_id);
	m_acceleration = Vehicle::getAcceleration(m_id);
	libsumo::TraCIPosition p = Vehicle::getPosition(m_id);
	m_position.x = p.x;
	m_position.y = p.y;
}

VehicleDIY::VehicleDIY(const VehicleDIY &veh) {
	m_id = veh.m_id;
	m_speed = veh.m_speed;
	m_type_id = veh.m_type_id;
	m_length = veh.m_length;
	m_route = veh.m_route;
	m_lane_id = veh.m_lane_id;
	m_acceleration = veh.m_acceleration;
	m_position = veh.m_position;
}

double VehicleDIY::get_distance() const {
	return sqrt(m_position.x * m_position.x + m_position.y * m_position.y);
}

double VehicleDIY::get_expect_arrival_time() const {
	if(m_speed < 1e-5) {
		// speed is zero
		return 0;
	}

	double s = sqrt(m_position.x * m_position.x + m_position.y * m_position.y);
	if(m_acceleration > 0) {
		// speed up
		double delta = m_speed * m_speed + 2 * m_acceleration * s;
		return (-m_speed + sqrt(delta)) / m_acceleration;
	} else if(m_acceleration < 1e-5) {
		// speed is even 
		return s / m_speed;
	} else {
		// slow down
		double t = m_speed / m_acceleration;
		double slow_down_dist = m_speed * t + m_acceleration * t * t / 2;
		if(slow_down_dist < s) {
			return t;
		}
		double delta = m_speed * m_speed + 2 * m_acceleration * s;
		return (-m_speed + sqrt(delta)) / m_acceleration;
	}
}

void VehicleDIY::print_vehicle() const {
	cout << "id: " << m_id << endl;
	cout << "length: " << m_length << endl;
	cout << "position: (" << m_position.x << ", " << m_position.y << ")" << endl;
	cout << "lane: " << m_lane_id << endl;
	cout << "accleration: " << m_acceleration << endl;
	cout << "speed: " << m_speed << endl;
	cout << "route: ";
	for(size_t i = 0; i != m_route.size(); ++i) {
		cout << m_route[i] << ", ";
	}
	cout << endl << "arrival time: " << get_expect_arrival_time() << endl;
}

string VehicleDIY::get_cur_edge() const {
	return m_lane_id.substr(0, m_lane_id.find("_"));
}

vector<string> VehicleDIY::get_route() const {
	return m_route;
}
