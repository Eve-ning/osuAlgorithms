// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "class/OsuMap.h"
#include "OsuAlg.h"

int main()
{
	OsuMap map = OsuMap("map.txt");
	std::cout << OsuAlg::count(map.hitObjectList());
}