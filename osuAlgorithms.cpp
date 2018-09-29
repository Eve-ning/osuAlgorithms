// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"
#include "PatternRecognition.h"

int main()
{
		OsuMap map = OsuMap("map.txt");

		//auto densityList = Density::runningDensity(map.hitObjectList(), 1500, 1000, true, 0);

		//int at = 0;

		//for (auto density : densityList) {
		//	std::cout << at*1000 << "ms :\t"<< density * 1000 << std::endl;
		//	at++;
		//}

		PatternRecognition newp = PatternRecognition(map.hitObjectList().sptr(),map.mapSettings().circleSize());
		Pattern newPattern = { {0}, {0} };

		double range = 1000;
		std::vector<RecogProperties> result = newp.run(newPattern, range);

		std::cout << "COL\t|\tOFFSET\t|\tVARIANCE" << std::endl;
		for (RecogProperties pattern : result) {
			std::cout << pattern.column << "\t|\t";
			std::cout << pattern.offset << "\t|\t";
			for (auto var : pattern.variance) {
				// We want to see the distance instead of the deviation
				std::cout << range - var << "\t";
			}
			std::cout << std::endl;
		}







}