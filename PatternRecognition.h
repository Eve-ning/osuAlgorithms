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

struct RecogProperties {
	RecogProperties(std::vector<double> newVariance, int newColumn, double newOffset) : variance(newVariance), column(newColumn), offset(newOffset) {}

	std::vector<double> variance;
	int column;
	double offset;
};

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
	std::vector<RecogProperties> run(Pattern pattern, double distance);


private:

	// Converts map to Vector[Column][Offset]
	void convertMap(const HitObjectList_sptr &objList);

	// Returns the results for checking the pattern, relative to the index
	// Y Index refers to the offset index of m_data
	// X Index refers to the column we are checking for
	// Pattern is anchored on the bottom left
	std::vector<double> patternThreshold(int column, double offset, Pattern pattern, double distance);

	// Checks the minimum offset existing in the range
	double checkInColumn(double min, double range, int column);


	std::vector<std::vector<double>> m_data;
	int m_keys;

};

