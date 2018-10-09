#pragma once
#include "../PatternRecognition.h"
#include "../Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class OSUParser
{
public:



	void DPC(const OsuMap &map);
	void Density(const OsuMap &map);

	void castDirectory(void(*castFunc) (const OsuMap &map), const std::string &dir = "../../../IO/osu/");

	void changeDensityRange(double range) {
		DENSITY_RANGE = range;
	}
    void changeDensityInterval(double interval) {
		DENSITY_INTERVAL = interval;
	}

private:


	void toMapCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap &map, std::vector<std::string> headers);

	double DENSITY_RANGE = 10000;
	double DENSITY_INTERVAL = 10000;

};

