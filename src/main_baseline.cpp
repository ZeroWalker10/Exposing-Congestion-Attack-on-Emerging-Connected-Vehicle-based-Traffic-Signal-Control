#include <iostream>
#include <string>
#include <libsumo/libtraci.h>
#include <libsumo/TrafficLight.h>

using namespace libtraci;
using namespace LIBSUMO_NAMESPACE;
using namespace std;

int main(int argc, char* argv[]) {
    Simulation::start({"sumo-gui", "-c", "congestion.sumocfg", "--quit-on-end", "--delay", "0"});
	int i = 0;
	while(Simulation::getMinExpectedNumber() > 0) {
		if(i % 200 == 0) {
			cout << "state: " << TrafficLight::getRedYellowGreenState("center") << endl;
		}
		Simulation::step();
	}
    Simulation::close();
	return 0;
}
