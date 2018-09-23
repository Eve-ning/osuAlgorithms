#pragma once
#include "General.h"

// This helps measure density in the chart in various ways
namespace Density
{
	// Counts the number of Objects within a range
	template <typename OsuList>
	double density(const OsuList &list, double lowerBound, double upperBound, bool inclusive = true) {
		return General::count(list, lowerBound, upperBound, inclusive) / (upperBound - lowerBound);
	}

	// Might be slow if we keep calling count, will test
	// Gets the list for running density
	// Range: How large of the density search should be
	// Interval: Distance to next search
	// Start: Where should the search start
	template <typename OsuList>
	std::vector<double> runningDensity(const OsuList &list, double range, double interval, bool inclusive = true, double start = 0) {

		if (interval <= 0) {
			throw new std::exception("Interval cannot be 0 or negative");
		}

		auto list_sptr = list.sptr();
		std::vector<double> densityList = {};

		std::vector<double> list_offset = {};
		for (auto obj : list_sptr) {
			list_offset.push_back(obj->offset());
		}

		// If the start isn't at the end
		while (start < *std::max_element(list_offset.begin(), list_offset.end())) {
			densityList.push_back(General::count(list, start, start + range, inclusive) / (range));
			start += interval;
		}

		return densityList;
	}
}

