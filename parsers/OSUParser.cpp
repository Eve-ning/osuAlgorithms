#include "pch.h"
#include "../pch.h"
#include "OSUParser.h"

// Prints Delta Per Column
void OSUParser::DPC() {
	PatternRecognition newp = PatternRecognition(m_mapData.hitObjectList().sptr(), (int)m_mapData.mapSettings().circleSize());
	auto dataList = newp.deltaPerColumn();
	std::vector <std::vector<double>> objectList;
	std::vector<double> object;

	for (auto data : dataList) {
		object = {};
		object.push_back(data.offset);
		object.push_back(data.column);
		object.push_back(data.delta);
		objectList.push_back(object);
	}

	toMapCSV(objectList, "/dpc_csv", std::vector<std::string>({ "Offset", "Column", "Delta" }));
}

// Prints Density
// Change the range and Density via changeDensityRange & changeDensityInterval

void OSUParser::Density(){

		auto densityList = Density::runningDensity(m_mapData.hitObjectList(), DENSITY_RANGE, DENSITY_INTERVAL, true, 0);

		int at = 0;

		std::vector<std::vector<double>> data;
		std::vector<double> row;

		for (auto density : densityList) {
			row = {};
			row.push_back(density.offset);
			row.push_back(density.density);
			at++;

			data.push_back(row);
		}

		toMapCSV(data, "density_csv", std::vector<std::string>({ "Offset", "Density" }));
}

// Casts this class' functions over a default Input directory, to output to default Output dir

void OSUParser::castDirectory(void(*castFunc)(const OsuMap &map)) {

	try {
		// txt will be the .osu or .txt file from Tests directory
		for (auto &txt : std::filesystem::directory_iterator(m_osuDir)) {
			std::cout << "Loading: " << txt.path() << std::endl;

			OsuMap map = OsuMap(txt.path().string());
			castFunc(map);
			std::cout << std::endl;
		}
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return;
	}
}

// Converts Map to CSV
void OSUParser::toMapCSV(std::vector<std::vector<double>> input, std::string folderName, std::vector<std::string> headers) {
	
	std::string artist = m_mapData.mapSettings().artist();
	std::string title = m_mapData.mapSettings().title();
	std::string creator = m_mapData.mapSettings().creator();
	std::string version = m_mapData.mapSettings().version();

	// We do this to prevent path problems
	std::replace(artist.begin(), artist.end(), '/', '_');
	std::replace(title.begin(), title.end(), '/', '_');
	std::replace(version.begin(), version.end(), '/', '_');
	std::replace(creator.begin(), creator.end(), '/', '_');

	std::string fileName = artist + " - " + title + " (" + creator + " - " + version + ")";

	General::toCSV<double>(folderName, fileName, headers, input);
}
