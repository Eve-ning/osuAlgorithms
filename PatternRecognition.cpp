#include "pch.h"
#include "PatternRecognition.h"

// Distance is how far from the current note to check
// Pattern MUST
// Range is the +/- of the expected distance (We will return the variance of the expected distance)
// We return the variance, in ms in doubles

std::vector<RecogProperties> PatternRecognition::run(Pattern pattern, double distance) {
	std::vector<RecogProperties> output = {};

	for (size_t column = 0; column < m_data.size(); column++) {
		for (double offset : m_data[column]) {

			// Offset defines EACH offset in the map

			// We push back the threshold vector for each pattern
			output.push_back(RecogProperties(patternThreshold(column, offset, pattern, distance), column, offset));
		}
	}

	return output;
}

// Converts map to Vector[Column][Offset]

void PatternRecognition::convertMap(const HitObjectList_sptr & objList) {
	/* old convert

	* We sort it so that we can tell which object will have similar offsets
	* std::sort(objList.begin(), objList.end(), [](HitObject_sptr a, HitObject_sptr b) -> bool {
	* 	return a->offset() < b->offset();
	* });
	*
	* // This holds the previous note offset, so we can tell if the following note has the same offset
	* int buffer = -1;
	* int indexCounter = -1;
	*
	* for (int x = 0; x < objList.size(); x++) {
	*
	* 	// If it matches buffer we push back into the same column
	* 	if (objList[x]->offset() == buffer) {
	* 		m_data[indexCounter].columnList.push_back(objList[x]->column());
	* 	}
	* 	else {
	* 		// Else we push back a new OffsetData
	* 		m_data.push_back(OffsetData(objList[x]->offset(), objList[x]->column(), m_keys));
	*
	* 		// So that the if statement pushes to the correct index
	* 		indexCounter++;
	*
	* 		// Set our buffer
	* 		buffer = objList[x]->offset();
	* 	}
	*}
	*/
	for (auto obj : objList) {
		m_data[(int)obj->column() - 1].push_back(obj->offset());
	}
	for (auto &column : m_data) {
		std::sort(column.begin(), column.end());
	}
	return;
}

// Returns the results for checking the pattern, relative to the index
// Y Index refers to the offset index of m_data
// X Index refers to the column we are checking for
// Pattern is anchored on the bottom left

std::vector<double> PatternRecognition::patternThreshold(int column, double offset, Pattern pattern, double distance) {
	std::vector<double> output = {};

	int findOffset = 0;

	for (size_t relative_y = 0; relative_y < pattern.size(); relative_y++) {
		for (auto relative_x : pattern[relative_y]) {

			// We skip checking the first note in the pattern as we anchor on the bottom left
			if (relative_x + relative_y == 0) {
				continue;
			}

			// If column exceeds keys we don't check it (outOfIndex)
			if (column + relative_x > m_keys) {
				continue;
			}

			// checkInColumn returns -1 if there isn't a offset there
			findOffset = checkInColumn(offset + (distance * (relative_y - 1)), distance, column + relative_x);

			if (findOffset != -1) {
				// Variance = offset + distance - findOffset 
				// Push Back Variance
				output.push_back(offset + distance - findOffset);
			}
		}
	}

	return output;
}

// Checks the minimum offset existing in the range

inline double PatternRecognition::checkInColumn(double min, double range, int column) {
	for (auto offset : m_data[column]) {
		if (offset > min + range) {
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
