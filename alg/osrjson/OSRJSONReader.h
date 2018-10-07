#pragma once
#include <fstream>
#include "../General.h"
#include <filesystem>

namespace OSRJSONReader
{
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

	void readFolder(const std::string &pathToReplayFolder = "../../../IO/osr_json/");
	void toOSRCSV(const std::string &fileName, std::vector<int> &timeframeList, const std::vector<KeyStatus> &keyStatusList);
	
};