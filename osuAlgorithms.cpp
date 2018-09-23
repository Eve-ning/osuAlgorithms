// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"

int main()
{
		OsuMap map = OsuMap("map.txt");

		auto densityList = Density::runningDensity(map.hitObjectList(), 2000, 1000, true, 0);

		for (auto density : densityList) {
			std::cout << density * 1000 << std::endl;
		}





}