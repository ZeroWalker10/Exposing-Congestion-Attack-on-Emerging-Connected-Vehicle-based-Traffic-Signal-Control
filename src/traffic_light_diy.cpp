#include <libsumo/libtraci.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include "traffic_light_diy.h"
#include "COP_DUAL_RING.h"

int MinGreen[8] = { 20, 20, 20, 20, 20, 20, 20, 20 };
int MaxGreen[8] = { 50, 50, 50, 50, 50, 50, 50, 50 };
int Yellow[8] = { 4, 4, 4, 4, 4, 4, 4, 4 };
int Red[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
int delay_type = 1;
char temp_log[512];
int LaneNo[8] = {0};
int ArrivalTable[131][8];
int RequestTable[8];
int queue_warning_P1;
int queue_warning_P5;
double red_elapse_time[8];
int PedWalk[8];
int PedClr[8];
int Ped_Phase_Considered[8];

int opt_sig_plan[2][2*2];
int opt_sig_seq[2][2*2];

using namespace LIBSUMO_NAMESPACE;
using namespace libsumo;
using namespace std;
using namespace libtraci;

int STAGE_PAIR[9] = {0, 6, 5, 8, 7, 2, 1, 4, 3};
int NICE_PAIR[9] = {0, 5, 6, 7, 8, 1, 2, 3, 4};
int CONVERT[9] = {0, 2, 5, 4, 7, 6, 1, 8, 3};
int RCONVERT[9] = {0, 6, 1, 8, 3, 2, 5, 4, 7};
int stages[2][4] = {{6, 1, 8, 3}, {2, 5, 4, 7}};
int real_skip[8];

TrafficLightDIY::TrafficLightDIY(const std::string &tl_id, const ArrivalTableDIY &at, const libsumo::TraCILogic &logic, const Attacker &attacker, double pene_ratio)
		: m_tl_id(tl_id), m_at(at), m_logic(logic), m_attacker(attacker), m_pene_ratio(pene_ratio) {
}

void TrafficLightDIY::copy_arrival_table() {
	// attack
	m_attacker.attack(m_at);

	vector<vector<int>> at = m_at.get_arrival_table();
	memset(RequestTable, 0, sizeof(int) * 8);
	for(int i = 0; i < 131; ++i) {
		for(int j = 0; j < 8; ++j) {
			ArrivalTable[i][j] = at[i][j];
			RequestTable[j] += at[i][j];
		}
	}
}

pair<int, vector<libsumo::TraCIPhase*>> TrafficLightDIY::update_signal_plan(std::vector<PhaseDIY> &phases) {
	static vector<libsumo::TraCIPhase> SET_PHASES;

	size_t total_lanes = 0;
	vector<int> start_lane(phases.size());
	for(size_t i = 0; i != phases.size(); ++i) {
		pair<int, int> lg = phases[i].get_last_green_plan();
		LaneNo[phases[i].get_id()-1] = static_cast<int>(phases[i].get_ctrl_lanes().size());
		total_lanes += phases[i].get_state_length();
	}

	// copy arrival table
	copy_arrival_table();

	int init_phases[2] = { 0 };
	int green_elapse[2];
	int passed_phases[2];
	int skip_phases[8] = { 0 };
	#if 0
	// last time, more green time and some vehicles request, this time first
	int green_time, first_phase;
	for(int i = 0; i < 4; ++i) {
		if(i == 0) {
			green_time = phases[stages[0][i] - 1].get_allocated_green_time();
			first_phase = stages[0][i];
		} else {
			if(green_time < phases[stages[0][i] - 1].get_allocated_green_time() &&
					RequestTable[stages[0][i] - 1] > 0) {
				green_time = phases[stages[0][i] - 1].get_allocated_green_time();
				first_phase = stages[0][i];
			}
		}
	}
	int second_phase;
	second_phase = NICE_PAIR[first_phase];
	green_time = phases[second_phase - 1].get_allocated_green_time();
	if(green_time < phases[STAGE_PAIR[second_phase] - 1].get_allocated_green_time() &&
			RequestTable[STAGE_PAIR[second_phase]- 1] > 0) {
		second_phase = STAGE_PAIR[second_phase];
	}
	#endif 
	// more waiting vehicles, more green time
	int which_phase = 1, waiting_vehicles = 0;
	int which_stage, which_ring;
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(RequestTable[stages[i][j] - 1] > waiting_vehicles) {
				waiting_vehicles = RequestTable[stages[i][j] - 1];
				which_phase = stages[i][j];
				which_stage = j < 2 ? 0 : 1;
				which_ring = i;
			}
		}
	}

	int first_phase, second_phase;
	if(which_ring == 0) {
		first_phase = which_phase;
		second_phase = NICE_PAIR[first_phase];
		waiting_vehicles = RequestTable[second_phase - 1];
		if(waiting_vehicles < RequestTable[STAGE_PAIR[second_phase] - 1]) {
			second_phase = STAGE_PAIR[second_phase];
		}
	} else {
		second_phase = which_phase;
		first_phase = NICE_PAIR[second_phase];
		waiting_vehicles = RequestTable[first_phase - 1];
		if(waiting_vehicles < RequestTable[STAGE_PAIR[first_phase] - 1]) {
			first_phase = STAGE_PAIR[first_phase];
		}
	}


	init_phases[0] = CONVERT[first_phase];
	init_phases[1] = CONVERT[second_phase];
	green_elapse[0] = 0; 
	green_elapse[1] = 0; 
	passed_phases[0] = passed_phases[1] = 0;
	for(int i = 0; i < 8; ++i) {
		skip_phases[i] = 0;
		for(int j = 0; j < 131; ++j) {
			if(ArrivalTable[j][i] > 0) {
				skip_phases[i] = 1;
				break;
			}
		}
	}
	for(int i = 0; i < 8; ++i) {
		real_skip[CONVERT[i+1] - 1] = skip_phases[i]; 
	}

	if(m_pene_ratio < 0.95) {
		// pest employment
		// TODO: EVLS
	}

	COP_DUAL_RING(init_phases, green_elapse, passed_phases, real_skip);
	if(opt_sig_seq[0][0] == 0 && opt_sig_seq[0][1] == 0) {
		if(opt_sig_plan[0][0] > 0) {
			opt_sig_seq[0][0] = init_phases[0];
		} else {
			opt_sig_seq[0][1] = init_phases[0];
		}
	}

	if(opt_sig_seq[1][0] == 0 && opt_sig_seq[1][1] == 0) {
		if(opt_sig_plan[1][0] > 0) {
			opt_sig_seq[1][0] = init_phases[1];
		} else {
			opt_sig_seq[1][1] = init_phases[1];
		}
	}

	// rconvert
	for(int i = 0; i < 4; ++i) {
		opt_sig_seq[0][i] = RCONVERT[opt_sig_seq[0][i]];
		opt_sig_seq[1][i] = RCONVERT[opt_sig_seq[1][i]];
	}

	for(int i = 0; i < 4; ++i) {
		switch(i) {
		case 0:
		case 2:
			if(opt_sig_seq[0][i] == 0 && opt_sig_seq[0][i+1] > 0) {
				opt_sig_seq[0][i] = STAGE_PAIR[opt_sig_seq[0][i+1]];
			}

			if(opt_sig_seq[1][i] == 0 && opt_sig_seq[1][i+1] > 0) {
				opt_sig_seq[1][i] = STAGE_PAIR[opt_sig_seq[1][i+1]];
			}
			break;
		case 1:
		case 3:
			if(opt_sig_seq[0][i] == 0 && opt_sig_seq[0][i-1] > 0) {
				opt_sig_seq[0][i] = STAGE_PAIR[opt_sig_seq[0][i-1]];
			}

			if(opt_sig_seq[1][i] == 0 && opt_sig_seq[1][i-1] > 0) {
				opt_sig_seq[1][i] = STAGE_PAIR[opt_sig_seq[1][i-1]];
			}
			break;
		}
	}

	// update phases
	vector<int> ps1;
	vector<int> ps2;
	vector<pair<int, char>> ss1; // duration, state
	vector<pair<int, char>> ss2;
	for(int i = 0; i < 4; ++i) {
		if(opt_sig_plan[0][i] > 0 || opt_sig_plan[1][i] > 0) {
			if(opt_sig_plan[0][i] > 0) {
				ps1.push_back(opt_sig_seq[0][i] - 1);
				ps1.push_back(opt_sig_seq[0][i] - 1);
				ps1.push_back(opt_sig_seq[0][i] - 1);
				ss1.push_back(make_pair(opt_sig_plan[0][i], 'g'));
				ss1.push_back(make_pair(4, 'y'));
				ss1.push_back(make_pair(2, 'r'));
			}

			if(opt_sig_plan[1][i] > 0) {
				ps2.push_back(opt_sig_seq[1][i] - 1);
				ps2.push_back(opt_sig_seq[1][i] - 1);
				ps2.push_back(opt_sig_seq[1][i] - 1);
				ss2.push_back(make_pair(opt_sig_plan[1][i], 'g'));
				ss2.push_back(make_pair(4, 'y'));
				ss2.push_back(make_pair(2, 'r'));
			}

		}
	}

	int i = 0,j = 0;	
	int phase_index = 0;
	vector<vector<pair<char, int>>> ss(phases.size());
	int cop_time = 0;
	char r = 'r';
	string s(total_lanes, r);
	while(i < ps1.size() && j < ps2.size()) {
		if(ss1[i].first== 0) {
			++i;
			continue;
		}

		if(ss2[j].first == 0) {
			++j;
			continue;
		}

		int dur = min(ss1[i].first, ss2[j].first);
		s.assign(total_lanes, r);
		size_t len = phases[ps1[i]].get_state_pos() + phases[ps1[i]].get_state_length();
		for(size_t m = phases[ps1[i]].get_state_pos(); m != len; ++m) {
			s[m] = ss1[i].second;
		}

		len = phases[ps2[j]].get_state_pos() + phases[ps2[j]].get_state_length();
		for(size_t m = phases[ps2[j]].get_state_pos(); m < len; ++m) {
			s[m] = ss2[j].second;
		}

		if(phase_index < SET_PHASES.size()) {
			SET_PHASES[phase_index] = libsumo::TraCIPhase(dur, s, dur, dur);
		} else {
			SET_PHASES.push_back(libsumo::TraCIPhase(dur, s, dur, dur));
		}

		for(int k = 0; k < static_cast<int>(phases.size()); ++k) {
			if(k == ps1[i]) {
				ss[k].push_back(make_pair(ss1[i].second, dur));
			} else if(k == ps2[j]) {
				ss[k].push_back(make_pair(ss2[j].second, dur));
			} else {
				ss[k].push_back(make_pair(r, dur));
			}
		}
		++phase_index;
		cop_time += dur;

		ss1[i].first -= dur;
		ss2[j].first -= dur;
	}

	for(size_t i = 0; i != phases.size(); ++i) {
		phases[i].set_state(ss[phases[i].get_id() - 1]);
	}

	vector<libsumo::TraCIPhase*> ps;
	for(int i = 0; i < phase_index; ++i) {
		ps.push_back(&SET_PHASES[i]);
	}

	return make_pair(cop_time, ps); 
}
