#pragma once
#include "../alg/DPC.h"
#include "../alg/Density.h"
#include <fstream>
#include <iostream>
#include <filesystem>

class OSUParser
{
public:

	struct DPCData {
		DPCData(std::vector<double> newOffsetList, std::vector<int> newColumnList, std::vector<double> newDeltaList) :
			offsetList(newOffsetList), columnList(newColumnList), deltaList(newDeltaList) {}
		DPCData() : offsetList({}), columnList({}), deltaList({}) {}

		std::vector<double> offsetList;
		std::vector<int> columnList;
		std::vector<double> deltaList;
	};

	struct DensityData {
		DensityData(std::vector<double> newOffsetList, std::vector<double> newDensityList) :
			offsetList(newOffsetList), densityList(newDensityList) {}
		DensityData() : offsetList({}), densityList({}) {}

		std::vector<double> offsetList;
		std::vector<double> densityList;
	};

	OSUParser(const std::string &osuFileName) : m_mapData(OsuMap(m_osuDir + osuFileName)) {}
	OSUParser(const OsuMap &mapData) : m_mapData(mapData) {}

	DPCData DPC(bool export = false);
	DensityData Density(bool export = false);

	void changeDensityRange(double range) {
		DENSITY_RANGE = range;
	}
    void changeDensityInterval(double interval) {
		DENSITY_INTERVAL = interval;
	}

private:

	std::string m_osuDir = "../../../IO/osu/";

	OsuMap m_mapData;

	std::string getFileName();

	double DENSITY_RANGE = 10000;
	double DENSITY_INTERVAL = 10000;


};

