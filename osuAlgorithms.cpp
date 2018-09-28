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

		PatternRecognition newp = PatternRecognition(map.hitObjectList().sptr(),4);
		Pattern newPattern = { {0}, {0} };
		auto result = newp.run(newPattern, 1000);

		for (auto pattern : result) {
			
			std::cout << "{ ";
			for (auto threshold : pattern) {
				std::cout << threshold << ", ";
			}
			std::cout << " }" << std::endl;
		}





}