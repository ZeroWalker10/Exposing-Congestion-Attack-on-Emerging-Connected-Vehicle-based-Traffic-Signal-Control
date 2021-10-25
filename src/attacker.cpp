#include "attacker.h"

Attacker::Attacker(bool active, int i, int j, bool smart)
		: m_active(active), m_i(i), m_j(j), m_smart(smart) {
}

void Attacker::attack(ArrivalTableDIY &at) {
	if(m_active) {
		if(!m_smart) {
			at.increase_arrival_table(m_i, m_j, 1);
		}
	}
}
