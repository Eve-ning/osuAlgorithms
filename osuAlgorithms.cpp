// osuAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "pch.h"
#include "class/OsuMap.h"
#include "alg/General.h"
#include "alg/Density.h"
#include "alg/PatternRecognition.h"
#include "alg/printing/OSUParser.h"
#include "alg/osrjson/OSRJSONParser.h"



int main()
{
	OSRJSONParser::readFolder();
}

 