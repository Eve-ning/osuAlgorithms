#pragma once

class DPC
{
public:

	struct DPCData {

		DPCData(int newColumn, double newdelta, double newOffset) : column(newColumn), delta(newdelta), offset(newOffset) {}

		int column;
		double delta;
		double offset;
	};

	DPC(const HitObjectList_sptr &objList, int keys) : m_keys(keys) {
		for (int k = 0; k < keys; k++) { m_dataAsVector.push_back({}); }
		read(objList);
	}

	// Calculates the time between pressing a note again in the same column
	std::vector<DPCData> deltaPerColumn();

private:

	// Converts map to Vector[Column][Offset]
	void read(const HitObjectList_sptr &objList);
	// Checks the minimum offset existing in the range
	double matchOffset(double min, int column, double threshold = 10000);

	std::vector<std::vector<double>> m_dataAsVector;
	int m_keys;

};

