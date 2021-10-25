#ifndef TIME_SCHEDULE_H
#define TIME_SCHEDULE_H

#include<libsumo/libtraci.h>
#include<string>
#include<vector>

enum TL_UPDATE_MODE {
	LOGIC, ITERATOR
};

class TimeSchedule {
public:
	TimeSchedule(TL_UPDATE_MODE mode)
		: m_mode(mode) {
	}
	TimeSchedule(const std::string &tl_id, TL_UPDATE_MODE mode, int start_time);
	void update_phases(int start_time, const std::vector<libsumo::TraCIPhase*> &phases);
	void update(int cur_time);
	void set_tl_id(const std::string &tl_id) {
		m_tl_id = tl_id;
	}
	void set_start_time(int start_time) {
		m_start_time = start_time;
	}
private:
	std::string m_tl_id;
	std::vector<libsumo::TraCIPhase*> m_phases;
	TL_UPDATE_MODE m_mode;
	int m_start_time;
};

#endif
