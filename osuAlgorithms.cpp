// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "class/OsuMap.h"
#include "OsuAlg.h"

int main()
{
	OsuMap map = OsuMap("map.txt");
	map.setTimingPointList(OsuAlg::moveTo(map.timingPointList(), 1000000.0, false));
	
	for (auto TP : map.timingPointList().sptr()) {
		std::cout << TP->str().c_str() << std::endl;
	}
}