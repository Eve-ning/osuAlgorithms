#pragma once
#include <fstream>
#include "../alg/General.h"
#include <filesystem>

class OSRJSONParser
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

	struct OSRJSONData {
		// Reads Data from File Path
		OSRJSONData(const std::string &filePath);

		// Construct from values
		OSRJSONData(std::vector<int> newTimeframeList, std::vector<KeyStatus> newKeyStatusList)
			: timeframeList(newTimeframeList), keyStatusList(newKeyStatusList){}

		std::vector<int> timeframeList;
		std::vector<KeyStatus> keyStatusList;
	};

	// Read a JSON from the default dir, specified in m_jsonDir
	OSRJSONParser(const std::string &jsonFileName) : m_jsonData(OSRJSONData(m_jsonDir + jsonFileName)) {}

	// Read a JSON from given data in OSRJSONData Format
	OSRJSONParser(const OSRJSONData &jsonData) : m_jsonData(jsonData) {}

	void toOSRCSV(const std::string &fileName);
	
	OSRJSONData jsonData() const {
		return m_jsonData;
	}

	// Get default directory for json files
	std::string jsonDir() const {
		return m_jsonDir;
	}

	// Change default directory for json files
	void setJsonDir(const std::string &jsonDir) {
		m_jsonDir = jsonDir;
	}

private:

	std::string m_jsonDir = "../../../IO/osr_json/";
	OSRJSONData m_jsonData;
};