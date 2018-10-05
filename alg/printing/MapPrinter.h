#pragma once
#include "../PatternRecognition.h"
#include "../Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class MapPrinter
{
public:

	static void DPC(const OsuMap &map);
	static void Density(const OsuMap &map);

	static void castDirectory(void(*castFunc) (const OsuMap &map), const std::string &inputPath = "Input", const std::string &outputPath = "Output");

	static void changeOutput(const std::string &filePath) {
		OUTPUT_PATH = filePath;
	}
	static void changeInput(const std::string &filePath) {
		INPUT_PATH = filePath;
	}

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

	static std::string OUTPUT_PATH;
	static std::string INPUT_PATH;
};

