// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "pch.h"
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"
#include "alg/DPC.h"
#include "parsers/OSRJSONParser.h"
#include "tests/Tests.h"

int main()
{
	auto testObj = Tests(OsuMap("map.txt"));
	testObj.densityTest();
	testObj.DPCTest();
}

 