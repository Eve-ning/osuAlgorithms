#include "pch.h"
#include "../../pch.h"
#include "MapAnalyse.h"

std::string MapAnalyse::OUTPUT_PATH = "Output";
std::string MapAnalyse::INPUT_PATH = "Input";
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


	toMapCSV(objectList, __FUNCTION__, map, std::vector<std::string>({ "Offset", "Column", "Delta" }));
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

		toMapCSV(data, __FUNCTION__, map, std::vector<std::string>({ "Offset", "Density" }));
}

// Casts this class' functions over a default Input directory, to output to default Output dir

void MapAnalyse::castDirectory(void(*castFunc)(const OsuMap &map), const std::string & inputPath, const std::string & outputPath) {

	changeInput(inputPath);
	changeOutput(outputPath);

	try {
		// txt will be the .osu or .txt file from Tests directory
		for (auto &txt : std::filesystem::directory_iterator("Tests\\" + INPUT_PATH)) {
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

void MapAnalyse::toMapCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap & map, std::vector<std::string> headers) {
	
	std::string artist = map.mapSettings().artist();
	std::string title = map.mapSettings().title();
	std::string creator = map.mapSettings().creator();
	std::string version = map.mapSettings().version();

	// We do this to prevent path problems
	std::replace(artist.begin(), artist.end(), '/', '_');
	std::replace(title.begin(), title.end(), '/', '_');
	std::replace(version.begin(), version.end(), '/', '_');
	std::replace(creator.begin(), creator.end(), '/', '_');

	// FileName includes the Class so we need to trim out the (CLASS::)
	fileName = fileName.substr(fileName.find(':') + 1);

	std::string outputPath = "Tests/" + OUTPUT_PATH + "/" + artist + " - " + title + " (" + creator + " - " + version + ")" + "(" + fileName + ").txt";

	General::toCSV<double>(outputPath, headers, input);
}
