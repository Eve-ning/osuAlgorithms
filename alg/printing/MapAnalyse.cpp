#include "pch.h"
#include "../../pch.h"
#include "MapAnalyse.h"

double MapAnalyse::DENSITY_RANGE = 10000;
double MapAnalyse::DENSITY_INTERVAL = 10000;

// Prints Delta Per Column

void MapAnalyse::DPC(const OsuMap & map) {
	PatternRecognition newp = PatternRecognition(map.hitObjectList().sptr(), (int)map.mapSettings().circleSize());
	auto dataList = newp.deltaPerColumn();
	std::vector < std::vector<double>> objectList;
	std::vector<double> object;

	for (auto data : dataList) {
		object = {};
		object.push_back(data.offset);
		object.push_back(data.column);
		object.push_back(data.delta);
		objectList.push_back(object);
	}


	toMapCSV(objectList, "/dpc_csv", map, std::vector<std::string>({ "Offset", "Column", "Delta" }));
}

// Prints Density
// Change the range and Density via changeDensityRange & changeDensityInterval

void MapAnalyse::Density(const OsuMap &map){

		auto densityList = Density::runningDensity(map.hitObjectList(), DENSITY_RANGE, DENSITY_INTERVAL, true, 0);

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

		toMapCSV(data, "density_csv", map, std::vector<std::string>({ "Offset", "Density" }));
}

// Casts this class' functions over a default Input directory, to output to default Output dir

void MapAnalyse::castDirectory(void(*castFunc)(const OsuMap &map),const std::string &dir) {

	try {
		// txt will be the .osu or .txt file from Tests directory
		for (auto &txt : std::filesystem::directory_iterator(dir)) {
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

// Converts 2D Vectors to a csv table format

void MapAnalyse::toMapCSV(std::vector<std::vector<double>> input, std::string folderName, const OsuMap & map, std::vector<std::string> headers) {
	
	std::string artist = map.mapSettings().artist();
	std::string title = map.mapSettings().title();
	std::string creator = map.mapSettings().creator();
	std::string version = map.mapSettings().version();

	// We do this to prevent path problems
	std::replace(artist.begin(), artist.end(), '/', '_');
	std::replace(title.begin(), title.end(), '/', '_');
	std::replace(version.begin(), version.end(), '/', '_');
	std::replace(creator.begin(), creator.end(), '/', '_');

	std::string fileName = artist + " - " + title + " (" + creator + " - " + version + ")";

	General::toCSV<double>(folderName, fileName, headers, input);
}
