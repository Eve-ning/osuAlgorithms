#pragma once
#include "../PatternRecognition.h"
#include "../Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class Printer
{
public:

	static void DPC(const OsuMap &map);
	static void Density(const OsuMap &map);

	static void castDirectory(const OsuMap &map, const std::string &inputPath, const std::string &outputPath, void(*castFunc) (const OsuMap &map));

	static void changeOutput(const std::string &filePath) {
		OUTPUT_PATH = filePath;
	}
	static void changeInput(const std::string &filePath) {
		INPUT_PATH = filePath;
	}

private:

	static void toCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap &map, std::vector<std::string> headers);

	static std::string OUTPUT_PATH;
	static std::string INPUT_PATH;
};

