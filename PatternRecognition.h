#pragma once

typedef std::vector<std::vector<int>> Pattern;
//
//class PatternDefinition {
//
//public:
//	// X & Y Flip defines Horizontal & Vertical Axis Mirroring respectively
//	PatternDefinition(std::vector<std::vector<bool>> pattern, bool xFlip = false, bool yFlip = false) : m_pattern(pattern) {}
//
//	// If we allow flips we will return more than 1 pattern
//	std::vector<Pattern> pattern() {
//		std::vector<Pattern> output = {};
//		output.push_back(m_pattern);
//
//		if (m_xFlip) {
//			output.push_back(rotateX());
//		}
//
//		if (m_yFlip) {
//			output.push_back(rotateY());
//		}
//
//		if (m_xFlip && m_yFlip) {
//			output.push_back(rotateXY());
//		}
//
//		return output;
//	}
//
//	Pattern rotateX() {
//		Pattern copy = m_pattern;
//		for (auto offset : copy) {
//			std::reverse(offset.begin(), offset.end());
//		}
//
//		return copy;
//	}
//	Pattern rotateY() {
//		Pattern copy = m_pattern;
//		std::reverse(copy.begin(), copy.end());
//
//		return copy;
//	}
//	Pattern rotateXY() {
//		Pattern copy = m_pattern;
//		for (auto offset : copy) {
//			std::reverse(offset.begin(), offset.end());
//		}
//		std::reverse(copy.begin(), copy.end());
//
//		return copy;
//	}
//
//private:
//	Pattern m_pattern;
//	bool m_xFlip;
//	bool m_yFlip;
//};


class PatternRecognition
{
public:
	PatternRecognition(const HitObjectList_sptr &objList, int keys) : m_keys(keys) {
		for (int k = 0; k < keys; k++) { m_data.push_back({}); }
		convertMap(objList);
	}
	
	// Distance is how far from the current note to check
	// Pattern MUST
	// Range is the +/- of the expected distance (We will return the variance of the expected distance)
	// We return the variance, in ms in doubles
	std::vector<std::vector<double>> run(Pattern pattern, double distance) {
		std::vector<std::vector<double>> output = {};

		for (size_t column = 0; column < m_data.size(); column++) {
			for (double offset : m_data[column]) {
				output.push_back(validatePattern(column, offset, pattern, distance));
			}
		}

		return output;
	}


private:

	// Converts map to Vector[Column][Offset]
	void convertMap(const HitObjectList_sptr &objList) {
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
			m_data[(int) obj->column() - 1].push_back(obj->offset());
		}
		return;
	}

	// Returns the results for checking the pattern, relative to the index
	// Y Index refers to the offset index of m_data
	// X Index refers to the column we are checking for
	// Pattern is anchored on the bottom left
	std::vector<double> validatePattern(int column, double offset, Pattern pattern, double distance) {
		std::vector<double> output = {};

		int findOffset = 0;

		for (size_t relative_y = 0; relative_y < pattern.size(); relative_y++ ) {
			for (auto relative_x : pattern[relative_y]) {

				if (relative_x + relative_y == 0) {
					continue;
				}

				if (column + relative_x > m_keys) {
					continue;
				}

				// Push Back Variance
				findOffset = checkInColumn(offset + (distance * (relative_y - 1)), distance, column + relative_x);

				if (findOffset != -1) {
					output.push_back(offset + distance - findOffset);
				}
			}
		}

		return output;
	}

	// Checks the minimum offset existing in the range
	double checkInColumn(double min, double range, int column) {
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


	std::vector<std::vector<double>> m_data;
	int m_keys;

};

