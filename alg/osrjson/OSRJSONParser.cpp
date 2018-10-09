#include "../../dependencies/json.hpp"
#include "pch.h"
#include "OSRJSONParser.h"

// Gets all the json in the specified folder and converts to csv
OSRJSONParser::OSRJSONParser(const std::string & jsonPath) {

	std::ifstream ifs(m_jsonDir + jsonPath);
	nlohmann::json osr = nlohmann::json::readFolder(ifs);

	// Analyse the data here
	std::vector<int> timeframeList;
	std::vector<KeyStatus> keyStatusList;

	// Timeframe indicates the timeframe when the key is pressed
	int timeframe = 0;

	// We have a buffer to check if the key combo has already been recorded
	// We don't need to record multiple of the same key combo
	KeyStatus keyStatusBuffer = KeyStatus();

	auto replay_data = osr["replay_data"];
	for (auto entry : replay_data) {
		KeyStatus keyStatus = KeyStatus(
			entry["keysPressed"]["Key1"],
			entry["keysPressed"]["Key2"],
			entry["keysPressed"]["Key3"],
			entry["keysPressed"]["Key4"],
			entry["keysPressed"]["Key5"],
			entry["keysPressed"]["Key6"],
			entry["keysPressed"]["Key7"]
		);
		if (!(keyStatus == keyStatusBuffer)) {
			keyStatusList.push_back(keyStatus);
			timeframeList.push_back(timeframe += entry["timeSinceLastAction"]);
			keyStatusBuffer = keyStatus;
		}
		else {
			// We still have to add the timeframe even though key status doesn't match
			timeframe += entry["timeSinceLastAction"];
		}
	}		

	m_jsonData.timeframeList = timeframeList;
	m_jsonData.keyStatusList = keyStatusList;
}

// Gets data from readFolder to convert to csv
void OSRJSONParser::toOSRCSV(const std::string & fileName) {
	std::ofstream output;

	std::vector<std::string> headers = { "Offset", "K1", "K2", "K3" , "K4" , "K5" , "K6" , "K7" };

	// Concatenate onto timeframeList 
	std::vector<std::vector<int>> data = { {} };
	std::vector<int> row = {};

	for (size_t x = 0; x < m_jsonData.timeframeList.size(); x++) {
		row = {};
		row.push_back(m_jsonData.timeframeList[x]);
		row.push_back(m_jsonData.keyStatusList[x].k1);
		row.push_back(m_jsonData.keyStatusList[x].k2);
		row.push_back(m_jsonData.keyStatusList[x].k3);
		row.push_back(m_jsonData.keyStatusList[x].k4);
		row.push_back(m_jsonData.keyStatusList[x].k5);
		row.push_back(m_jsonData.keyStatusList[x].k6);
		row.push_back(m_jsonData.keyStatusList[x].k7);

		data.push_back(row);
	}
	
	// Call General function to generate csv
	General::toCSV("osr_csv", fileName, headers, data);
}


