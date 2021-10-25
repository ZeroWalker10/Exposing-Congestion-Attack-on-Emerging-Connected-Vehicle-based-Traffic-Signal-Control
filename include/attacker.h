#ifndef ATTACKER_H
#define ATTACKER_H

#include "arrival_table_diy.h"

class Attacker {
public:
	Attacker(bool active, int i = 0, int j = 0, bool smart=false);
	void attack(ArrivalTableDIY &at);
	void update_attack_target(int i, int j) {
		m_i = i;
		m_j = j;
	}
	void activate() {
		m_active = true;
	}
	void disactivate() {
		m_active = false;
	}
private:
	bool m_active;
	int m_i, m_j;
	bool m_smart;
};

#endif
