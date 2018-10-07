#pragma once
#include "General.h"

// This helps measure density in the chart in various ways
namespace Density
{
	// Counts the number of Objects within a range and divides it by the range
	// Returns Notes/ms
	template <typename OsuList>
	double Density(const OsuList &list, double lowerBound, double upperBound, bool inclusive = true) {
		return General::count(list, lowerBound, upperBound, inclusive) / (upperBound - lowerBound);
	}

	struct DensityData {
		DensityData(double newOffset, double newDensity) : offset(newOffset), density(newDensity) {}

		double offset;
		double density;
	};

	// Gets the list for running density
	// Range: How large of the density search should be
	// Interval: Distance to next search
	// Start: Where should the search start
	// Returns Notes/ms
	template <typename OsuList>
	std::vector<DensityData> runningDensity(const OsuList &list, double range, double interval, bool inclusive = true, double start = 0) {

		if (interval <= 0) {
			throw new std::exception("Interval cannot be 0 or negative");
		}

		auto list_sptr = list.sptr();

		std::vector<double> densityList = {};
		std::vector<double> offsetList = {};

		std::vector<DensityData> output;

		// Convert to Offset list
		for (auto obj : list_sptr) {
			offsetList.push_back(obj->offset());
		}

		double density;
		
		// If the start isn't at the end
		while (start < *std::max_element(offsetList.begin(), offsetList.end())) {

			// Calculate density
			density = General::count(list, start, start + range, inclusive) / (range);
			densityList.push_back(density);

			// Append to output
			output.push_back(DensityData(start, density));

			// Move to next range to check
			start += interval;
		}

		return output;
	}
}

