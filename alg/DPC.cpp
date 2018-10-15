#include "pch.h"
#include "../pch.h"
#include "DPC.h"


// Converts map to Vector[Column][Offset]

void DPC::read(const HitObjectList_sptr & objList) {

	// Finds pushes offsets according to its column
	for (auto obj : objList) {
		// ->column() returns index from 1 (we need to minus 1)
		m_dataAsVector[(int)obj->column() - 1].push_back(obj->offset());
	}
	for (auto &column : m_dataAsVector) {
		// We sort because of 2 different offset sets being parsed
		std::sort(column.begin(), column.end());
	}
	return;
}

std::vector<DPC::DPCData> DPC::deltaPerColumn()
{
	std::vector<DPCData> output;

	double offset = 0;
	double nextOffset = 0;

	for (size_t column = 0; column < m_dataAsVector.size(); column++) {
		for (size_t offsetIndex = 0; offsetIndex < m_dataAsVector[column].size() - 1; offsetIndex++) {

			offset = m_dataAsVector[column][offsetIndex];
			nextOffset = m_dataAsVector[column][offsetIndex + 1]; // outOfIndex circumvented via size() - 1

			output.push_back(DPCData(column, nextOffset - offset, offset));
		}
	}

	return output;
}

// Matches the minimum offset existing in the range
// Returns -1 on fail
// !! IMPORTANT DEFAULT THRESHOLD FOR TESTING ONLY

double DPC::matchOffset(double min, int column, double threshold) {
	for (auto offset : m_dataAsVector[column]) {
		if (offset > min + threshold) {
			return -1;
		}
		else if (offset > min) {
			return offset;
		}
		else {
			continue;
		}
	}
	return -1;
}
