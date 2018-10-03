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
#include "alg/printing/Printer.h"


int main()
{
	Printer::castDirectory(Printer::DPC);
	Printer::castDirectory(Printer::Density);
}

