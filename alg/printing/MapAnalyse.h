#pragma once
#include "../PatternRecognition.h"
#include "../Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class MapAnalyse
{
public:

	static void DPC(const OsuMap &map);
	static void Density(const OsuMap &map);

	static void castDirectory(void(*castFunc) (const OsuMap &map), const std::string &dir = "../../../IO/osu/");

	static void changeDensityRange(double range) {
		DENSITY_RANGE = range;
	}
	static void changeDensityInterval(double interval) {
		DENSITY_INTERVAL = interval;
	}

private:

	static void toMapCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap &map, std::vector<std::string> headers);

	static double DENSITY_RANGE;
	static double DENSITY_INTERVAL;

};

