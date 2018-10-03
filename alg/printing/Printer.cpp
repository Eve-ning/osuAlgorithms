#include "pch.h"
#include "../../pch.h"
#include "Printer.h"

std::string Printer::OUTPUT_PATH = "Output";
std::string Printer::INPUT_PATH = "Input";

void Printer::DPC(const OsuMap & map) {
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


	toCSV(objectList, __FUNCTION__, map, std::vector<std::string>({ "Offset", "Column", "Delta" }));
}

void Printer::Density(const OsuMap &map){

		double range = 10000;
		double interval = 10000;

		auto densityList = Density::runningDensity(map.hitObjectList(), range, interval, true, 0);

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

		toCSV(data, __FUNCTION__, map, std::vector<std::string>({ "Offset", "Density" }));
}

void Printer::castDirectory(void(*castFunc)(const OsuMap &map), const std::string & inputPath, const std::string & outputPath) {

	changeInput(inputPath);
	changeOutput(outputPath);

	try {
		for (auto &txt : std::filesystem::directory_iterator("Tests\\" + INPUT_PATH)) {
			std::cout << "Loading: " << txt.path();

			OsuMap map = OsuMap(txt.path().string());
			castFunc(map);
		}
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return;
	}
}

void Printer::toCSV(std::vector<std::vector<double>> input, std::string fileName, const OsuMap & map, std::vector<std::string> headers) {

	std::ofstream output;
	std::string artist = map.mapSettings().artist();
	std::string title = map.mapSettings().title();
	std::string creator = map.mapSettings().creator();
	std::string version = map.mapSettings().version();

	// We do this to prevent path problems
	std::replace(artist.begin(), artist.end(), '/', '_');
	std::replace(title.begin(), title.end(), '/', '_');
	std::replace(version.begin(), version.end(), '/', '_');
	std::replace(creator.begin(), creator.end(), '/', '_');
	fileName = fileName.substr(9);

	std::string outputPath = "Tests/" + OUTPUT_PATH + "/" + artist + " - " + title + " (" + creator + " - " + version + ")" + "(" + fileName + ").txt";

	output.open(outputPath);

	if (!output.is_open()) {
		std::cout << "Failed to Open: " <<  outputPath << std::endl;
		return;
	}

	// Generate Headers
	for (size_t i = 0; i < headers.size(); i++) {
		output << headers[i].c_str();
		if (i < headers.size() - 1) {
			output << ",";
		}
	}
	output << std::endl;

	size_t commaCounter = 0;

	for (auto row : input) {
		commaCounter = 0;
		for (auto cell : row) {
			output << cell;

			// Comma Counter is to prevent the last comma
			if (commaCounter < row.size() - 1) {
				output << ",";
				commaCounter++;
			}
		}
		output << std::endl;
	}

	output.close();
}
