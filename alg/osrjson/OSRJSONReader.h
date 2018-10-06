#pragma once
#include <fstream>
#include "../General.h"
#include <filesystem>


class OSRJSONReader
{
public:
	struct KeyStatus {
		KeyStatus() :
			k1(false), k2(false), k3(false), k4(false), k5(false), k6(false), k7(false) {}
		KeyStatus(bool key1, bool key2, bool key3, bool key4, bool key5, bool key6, bool key7) :
			k1(key1), k2(key2), k3(key3), k4(key4), k5(key5), k6(key6), k7(key7) {}

		bool k1;
		bool k2;
		bool k3;
		bool k4;
		bool k5;
		bool k6;
		bool k7;

		bool operator ==(const KeyStatus &other) {
			return
				k1 == other.k1 &&
				k2 == other.k2 &&
				k3 == other.k3 &&
				k4 == other.k4 &&
				k5 == other.k5 &&
				k6 == other.k6 &&
				k7 == other.k7;
		}

		// We plan on analyzing to k7 only, so we omit >k7
		// bool k8 = false;
		// bool k9 = false;
		// bool k10 = false;
	};

	OSRJSONReader() {
		std::string pathToReplayFolder;
		std::vector<std::string> replayFiles = {};

		for (auto &txt : std::filesystem::directory_iterator(pathToReplayFolder)) {
			std::ifstream ifs(txt.path());
			nlohmann::json osr = nlohmann::json::parse(ifs);

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
			toOSRCSV(txt.path().string(), timeframeList, keyStatusList);
		}
		

		
	}
	~OSRJSONReader();

	void toOSRCSV(const std::string &fileName, std::vector<int> &timeframeList, const std::vector<KeyStatus> &keyStatusList) {
		std::ofstream output;

		std::vector<std::string> headers = { "Offset", "K1", "K2", "K3" , "K4" , "K5" , "K6" , "K7" };

		std::string outputPath = fileName + ".txt";

		// Concatenate onto timeframeList
		std::vector<std::vector<int>> data = { {} };
		std::vector<int> row = {};

		for (size_t x = 0; x < timeframeList.size(); x++) {
			row = {};
			row.push_back(timeframeList[x]);
			row.push_back(keyStatusList[x].k1);
			row.push_back(keyStatusList[x].k2);
			row.push_back(keyStatusList[x].k3);
			row.push_back(keyStatusList[x].k4);
			row.push_back(keyStatusList[x].k5);
			row.push_back(keyStatusList[x].k6);
			row.push_back(keyStatusList[x].k7);

			data.push_back(row);
		}
		General::toCSV(fileName, headers, data);
	}
	
};