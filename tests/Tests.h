#pragma once
class Tests
{
public:
	Tests(const OsuMap map) : m_map(map) {}
	
	// Runs the Density test

	void densityTest() {
		std::cout << "-- RUNNING Density Test -- " << std::endl;

		auto densityData = Density::runningDensity(m_map.timingPointList(), 20000, 20000);
		for (auto entry : densityData) {
			std::cout << entry.offset << "ms | " << entry.density << "n/ms" << std::endl;
		}
	}

	// Runs the Delta Per Column test

	void DPCTest() {
		std::cout << "-- RUNNING Delta Per Column Test -- " << std::endl;

		auto DPCObj = DPC(m_map.hitObjectList().sptr(), (int) m_map.mapSettings().circleSize());
		auto DPCData = DPCObj.deltaPerColumn();
		for (auto entry : DPCData) {
			std::cout << entry.offset << "ms | " << entry.column << "col | " << entry.delta << "dlt" << std::endl;
		}
	}


private:
	OsuMap m_map;
};

