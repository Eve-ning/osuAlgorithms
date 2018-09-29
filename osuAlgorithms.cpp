// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"
#include "alg/PatternRecognition.h"

void toCSV(std::vector<std::vector<double>> input, std::string fileName) {

	std::ofstream output;
	output.open("customOutput/" + fileName + ".txt");
	for (auto row : input) {
		for (auto cell : row) {
			output << cell;
			if (cell != row.back()) {
				output << ",";
			}
		}
		output << std::endl;
	}
}

void testRecog(const OsuMap &map) {
	PatternRecognition newp = PatternRecognition(map.hitObjectList().sptr(), map.mapSettings().circleSize());
	Pattern newPattern = { {0}, {0} };

	double range = 1000;
	std::vector<RecogProperties> result = newp.run(newPattern, range);
	std::vector<std::vector<double>> data;
	std::vector<double> row;
	for (RecogProperties pattern : result) {
		row = {};
		row.push_back(pattern.column);
		row.push_back(pattern.offset);
		for (auto var : pattern.variance) { row.push_back(range - var); }
		//
		//std::cout << pattern.column << "\t|\t";
		//std::cout << pattern.offset << "\t|\t";
		//for (auto var : pattern.variance) {
		//	// We want to see the distance instead of the deviation
		//	std::cout << range - var << "\t";
		//}
		//std::cout << std::endl;
		data.push_back(row);
		
	}

	toCSV(data, "PatternRecognition");
}

void testDensity(const OsuMap &map) {

	double range = 1500;
	double interval = 1000;

	auto densityList = Density::runningDensity(map.hitObjectList(), range, interval, true, 0);

	int at = 0;

	std::vector<std::vector<double>> data;
	std::vector<double> row;

	for (auto density : densityList) {
		row = {};
		row.push_back(at*range);
		row.push_back(density*range);
		at++;

		data.push_back(row);
	}

	toCSV(data, "Density");
}



int main()
{
		OsuMap map = OsuMap("map.txt");


		testRecog(map);
		testDensity(map);


}

