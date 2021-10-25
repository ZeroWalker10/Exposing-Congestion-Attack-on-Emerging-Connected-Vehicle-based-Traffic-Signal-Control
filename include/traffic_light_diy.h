#ifndef TRAFFIC_LIGHT_DIY_H
#define TRAFFIC_LIGHT_DIY_H

#include <string>
#include <vector>
#include <libsumo/TraCIDefs.h>
#include <libsumo/TrafficLight.h>
#include "arrival_table_diy.h"
#include "phase_diy.h"
#include "attacker.h"

class TrafficLightDIY {
public:
	TrafficLightDIY(const std::string &tl_id, const ArrivalTableDIY &at, const libsumo::TraCILogic &logic, const Attacker &attacker, double pene_ratio=1.0);
	std::pair<int, std::vector<libsumo::TraCIPhase*>> update_signal_plan(std::vector<PhaseDIY> &phases);	

private:
	void copy_arrival_table();
private:
	std::string m_tl_id;
	ArrivalTableDIY m_at;
	double m_pene_ratio;
	libsumo::TraCILogic m_logic;
	Attacker m_attacker;
};

#endif
