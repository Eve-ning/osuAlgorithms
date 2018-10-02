// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"
#include "alg/PatternRecognition.h"

void toCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap &map, std::vector<std::string> headers) {

	std::ofstream output;
	std::string artist = map.mapSettings().artist();
	std::string title = map.mapSettings().title();
	std::string creator = map.mapSettings().creator();
	
	// We do this to prevent path problems
	std::replace(artist.begin(), artist.end(), '/', '_');
	std::replace(title.begin(), title.end(), '/', '_');
	std::replace(creator.begin(), creator.end(), '/', '_');

	output.open("customOutput/" + artist + " - " + title + " (" + creator + ")" + "(" + fileName + ").txt");

	// Generate Headers
	for (int i = 0; i < headers.size(); i++) {
		output << headers[i].c_str();
		if (i < headers.size() - 1) {
			output << ",";
		}
	}
	output << std::endl;

	int commaCounter = 0;

	for (auto row : input) {
		commaCounter = 0;
		for (auto cell : row) {
			output << cell;

			// Comma Counter is to prevent the last comma
			if (commaCounter < row.size() - 1) {
				output << ",";
				commaCounter++;
			}
		}
		output << std::endl;
	}
}

void getDPC(const OsuMap &map) {
	PatternRecognition newp = PatternRecognition(map.hitObjectList().sptr(), (int) map.mapSettings().circleSize());
	auto dataList = newp.deltaPerColumn();
	std::vector < std::vector<double>> objectList;
	std::vector<double> object;

	for (auto data : dataList) {
		object = {};
		object.push_back(data.offset);
		object.push_back(data.column);
		object.push_back(data.delta);
		objectList.push_back(object);
	}


	toCSV(objectList, __FUNCTION__, map, std::vector<std::string>({"Offset", "Column", "Delta"}));
}

void getDensity(const OsuMap &map) {

	double range = 1500;
	double interval = 1000;

	auto densityList = Density::runningDensity(map.hitObjectList(), range, interval, true, 0);

	int at = 0;

	std::vector<std::vector<double>> data;
	std::vector<double> row;

	for (auto density : densityList) {
		row = {};
		row.push_back(density.offset);
		row.push_back(density.density);
		at++;

		data.push_back(row);
	}

	toCSV(data, __FUNCTION__, map, std::vector<std::string>({ "Offset", "Density" }));
}



int main()
{
		OsuMap map = OsuMap("map.txt");

		getDPC(map);
		getDensity(map);


}

