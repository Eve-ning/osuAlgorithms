#include "pch.h"
#include "../pch.h"

//#include "OSUParser.h"
//
//// Prints Delta Per Column
//OSUParser::DPCData OSUParser::DPC(bool export) {
//	DPC newp = DPC(m_mapData.hitObjectList().sptr(), (int)m_mapData.mapSettings().circleSize());
//	auto dataList = newp.deltaPerColumn();
//	std::vector <std::vector<double>> objectList;
//	DPCData output;
//
//	for (auto data : dataList) {
//		output.offsetList.push_back(data.offset);
//		output.columnList.push_back(data.column);
//		output.deltaList.push_back(data.delta);
//		if (export) {
//			objectList.push_back(std::vector<double>({ data.offset,(double)data.column,data.offset }));
//		}
//	}
//
//	std::vector<std::string> headers = { "Offset", "Column", "Delta" };
//
//	if (export) {
//		General::toCSV("dpc_csv", getFileName, headers, objectList);
//	}
//
//	return OSUParser::DPCData();
//}
//
//// Prints Density
//// Change the range and Density via changeDensityRange & changeDensityInterval
//
//OSUParser::DensityData OSUParser::Density(bool export){
//
//	auto densityList = Density::runningDensity(m_mapData.hitObjectList(), DENSITY_RANGE, DENSITY_INTERVAL, true, 0);
//
//	int at = 0;
//
//	std::vector<std::vector<double>> data;
//	std::vector<double> row;
//
//	for (auto density : densityList) {
//		row = {};
//		row.push_back(density.offset);
//		row.push_back(density.density);
//		at++;
//
//		data.push_back(row);
//	}
//
//	toMapCSV(data, "density_csv", std::vector<std::string>({ "Offset", "Density" }));
//}
//
//// Casts this class' functions over a default Input directory, to output to default Output dir
//
//void OSUParser::castDirectory(void(*castFunc)(const OsuMap &map)) {
//
//	try {
//		// txt will be the .osu or .txt file from Tests directory
//		for (auto &txt : std::filesystem::directory_iterator(m_osuDir)) {
//			std::cout << "Loading: " << txt.path() << std::endl;
//
//			OsuMap map = OsuMap(txt.path().string());
//			castFunc(map);
//			std::cout << std::endl;
//		}
//	}
//	catch (std::exception &e) {
//		std::cout << e.what() << std::endl;
//		return;
//	}
//}
//
//// Gets File Name
//std::string OSUParser::getFileName() {
//	
//	std::string artist = m_mapData.mapSettings().artist();
//	std::string title = m_mapData.mapSettings().title();
//	std::string creator = m_mapData.mapSettings().creator();
//	std::string version = m_mapData.mapSettings().version();
//
//	// We do this to prevent path problems
//	std::replace(artist.begin(), artist.end(), '/', '_');
//	std::replace(title.begin(), title.end(), '/', '_');
//	std::replace(version.begin(), version.end(), '/', '_');
//	std::replace(creator.begin(), creator.end(), '/', '_');
//
//	return artist + " - " + title + " (" + creator + " - " + version + ")";
//}
