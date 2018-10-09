#pragma once
#include "../alg/PatternRecognition.h"
#include "../alg/Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class OSUParser
{
public:

	OSUParser(const std::string &osuFileName) : m_mapData(OsuMap(m_osuDir + osuFileName)) {}
	OSUParser(const OsuMap &mapData) : m_mapData(mapData) {}

	void DPC();
	void Density();

	void castDirectory(void(*castFunc) (const OsuMap &map));

	void changeDensityRange(double range) {
		DENSITY_RANGE = range;
	}
    void changeDensityInterval(double interval) {
		DENSITY_INTERVAL = interval;
	}

private:

	std::string m_osuDir = "../../../IO/osu/";

	OsuMap m_mapData;

	void toMapCSV(std::vector<std::vector<double>> input, std::string fileName, std::vector<std::string> headers);

	double DENSITY_RANGE = 10000;
	double DENSITY_INTERVAL = 10000;

};

