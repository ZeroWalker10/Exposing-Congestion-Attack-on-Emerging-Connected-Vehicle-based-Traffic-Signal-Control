#include <libsumo/libtraci.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include "phase_diy.h"

using namespace std;
using namespace libtraci;

std::vector<PhaseDIY> PhaseDIY::init_phases(const std::string &tl_id, int &total_duration, libsumo::TraCILogic &logic) {
	vector<libsumo::TraCILogic> tls_logics = TrafficLight::getAllProgramLogics(tl_id);
	int phase_index = 0;

	// record phase point
	set<size_t> phase_points;
	logic = tls_logics[0];
	for(size_t i = 0; i != tls_logics[0].phases.size(); ++i) {
		char prev_stat = 0;
		string stats = tls_logics[0].phases[i]->state;
		for(int j = 0; j != stats.size(); ++j) {
			if(prev_stat != stats[j]) {
				phase_points.insert(j);
				prev_stat = stats[j];
			}
		}
	}

	vector<vector<pair<char, int>>> tl_stats(phase_points.size());
	set<size_t>::iterator iter;
	total_duration = 0;
	for(size_t i = 0; i != tls_logics[0].phases.size(); ++i) {
		int duration = tls_logics[0].phases[i]->duration;
		string stats = tls_logics[0].phases[i]->state;

		phase_index = 0;
		total_duration += duration;
		for(iter = phase_points.begin(); iter != phase_points.end(); ++iter) {
			char stat = tolower(stats[*iter]);
			if(tl_stats[phase_index].empty() || stat != tl_stats[phase_index].back().first) {
				tl_stats[phase_index].push_back(make_pair(stat, duration));
			} else {
				tl_stats[phase_index].back().second += duration;
			}
			++phase_index;
		}
	}

	// controlled edges
	vector<vector<libsumo::TraCILink>> ctrl_links = TrafficLight::getControlledLinks(tl_id);
	vector<set<pair<string, string>>> tl_edges(phase_points.size());
	vector<set<string>> tl_lanes(phase_points.size());
	size_t low, high;
	phase_index = 0;
	iter = phase_points.begin();
	vector<size_t> phase_poses;
	while(iter != phase_points.end()) {
		low = *iter;
		++iter;
		phase_poses.push_back(low);
		if(iter == phase_points.end()) {
			high = ctrl_links.size();
		} else {
			high = *iter;
		}

		for(size_t i = low; i != high; ++i) {
			for(size_t j = 0; j != ctrl_links[i].size(); ++j) {
				string f = ctrl_links[i][j].fromLane;
				string t = ctrl_links[i][j].toLane;
				tl_edges[phase_index].insert(make_pair(f.substr(0, f.find("_")), t.substr(0, t.find("_"))));
				tl_lanes[phase_index].insert(f);
			}
		}
		++phase_index;
	}

	// generate the initial phases
	vector<PhaseDIY> phases;
	for(size_t i = 0; i != tl_stats.size(); ++i) {
		phases.push_back(PhaseDIY(static_cast<int>(i + 1), tl_stats[i], tl_edges[i], tl_lanes[i]));  
		phases.back().set_state_pos(phase_poses[i]);
		if(i + 1 != tl_stats.size()) {
			phases.back().set_state_length(phase_poses[i+1] - phase_poses[i]);
		} else {
			phases.back().set_state_length(tls_logics[0].phases[0]->state.size() - phase_poses[i]);
		}
	}

	return phases; 
}

PhaseDIY::PhaseDIY(int id, const vector<pair<char, int> > &state, const set<pair<string, string> > &ctrl_edges, const set<string> &ctrl_lanes) 
			: m_id(id), m_state(state), m_ctrl_edges(ctrl_edges), m_ctrl_lanes(ctrl_lanes) {
}

int PhaseDIY::get_id() const {
	return m_id;
}

const vector<pair<char, int>>& PhaseDIY::get_state() const {
	return m_state;
}

const set<pair<string, string>>& PhaseDIY::get_ctrl_edges() const {
	return m_ctrl_edges;
}

bool PhaseDIY::is_vehicle_request(const vector<string> &route, const string &cur_edge) {
	int edge_pos = 0, phase_pos = -1;
	for(size_t i = 0; i + 1 < route.size(); ++i) {
		if(route[i] == cur_edge) {
			edge_pos = static_cast<int>(i);
		}

		set<pair<string, string> >::iterator iter = m_ctrl_edges.find(make_pair(route[i], route[i+1]));
		if(iter == m_ctrl_edges.end()) {
			continue;
		}

		phase_pos = static_cast<int>(i);
		break;
	}

	return edge_pos <= phase_pos;
}

const set<string>& PhaseDIY::get_ctrl_lanes() const {
	return m_ctrl_lanes;
}

pair<int, int> PhaseDIY::get_last_green_plan() const {
	int start_time = 0;
	int duration;
	int delta_duration = 0;
	int total_duration = 0;
	for(size_t i = 0; i != m_state.size(); ++i) {
		total_duration += m_state[i].second;
	}

	for(int i = static_cast<int>(m_state.size() - 1); i >= 0; --i) {
		if(m_state[i].first == 'g') {
			duration = m_state[i].second;
			start_time = total_duration - delta_duration - duration;
		} else {
			delta_duration += m_state[i].second;
		}
	}

	return make_pair(start_time, duration);
}

void PhaseDIY::set_state(const vector<pair<char, int>> &s) {
	m_state = s;
}
