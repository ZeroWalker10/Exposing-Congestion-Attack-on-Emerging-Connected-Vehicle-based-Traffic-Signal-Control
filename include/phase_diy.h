#ifndef PHASE_DIY_H
#define PHASE_DIY_H

#include <string>
#include <set>
#include <vector>
#include <utility>
#include <libsumo/TraCIDefs.h>

class PhaseDIY {
public:
	static std::vector<PhaseDIY> init_phases(const std::string &tl_id, int &total_duration, libsumo::TraCILogic &logic);
public:
	explicit PhaseDIY(int id, const std::vector<std::pair<char, int> > &state, const std::set<std::pair<std::string, std::string> > &ctrl_edges, const std::set<std::string> &ctrl_lanes);
	bool is_vehicle_request(const std::vector<std::string> &route, const std::string &cur_edge);
	int get_id() const;
	const std::vector<std::pair<char, int>>& get_state() const;
	const std::set<std::pair<std::string, std::string>>& get_ctrl_edges() const;
	std::pair<int, int> get_last_green_plan() const;
	const std::set<std::string>& get_ctrl_lanes() const;
	void set_state(const std::vector<std::pair<char, int>> &s);
	void set_state_pos(size_t state_pos) {
		m_state_pos = state_pos;
	}
	void set_state_length(size_t state_len) {
		m_state_len = state_len;
	}
	size_t get_state_pos() const {
		return m_state_pos;
	}
	size_t get_state_length() const {
		return m_state_len;
	}

	int get_allocated_green_time() const {
		int allocated = 0;
		for(size_t i = 0; i != m_state.size(); ++i) {
			if(m_state[i].first == 'g') {
				allocated += m_state[i].second;
			}
		}
		return allocated;
	}
private:
	int m_id;
	std::vector<std::pair<char, int> > m_state;		// r(g, y), duration
	std::set<std::pair<std::string, std::string> > m_ctrl_edges;
	std::set<std::string> m_ctrl_lanes;
	size_t m_state_pos;
	size_t m_state_len;
};

#endif
