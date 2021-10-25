#include "time_schedule.h"

using namespace std;
using namespace libtraci;

TimeSchedule::TimeSchedule(const std::string &tl_id, TL_UPDATE_MODE mode, int start_time) 
		: m_tl_id(tl_id), m_mode(mode), m_start_time(start_time) {
}

void TimeSchedule::update_phases(int start_time, const std::vector<libsumo::TraCIPhase*> &phases) {
	m_start_time = start_time;
	m_phases = phases;
}

void TimeSchedule::update(int cur_time) {
	int start_time = m_start_time;
	int end_time;
	for(size_t i = 0; i != m_phases.size(); ++i) {
		end_time = start_time + m_phases[i]->duration;
		if(cur_time >= start_time && cur_time <= end_time) {
			TrafficLight::setRedYellowGreenState(m_tl_id, m_phases[i]->state);
			break;
		}

		start_time = end_time;
	}
}
