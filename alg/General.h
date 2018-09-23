#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "class/OsuMap.h"

namespace General
{
	// Counts the number of Objects
	template <typename OsuList>
    int count(const OsuList &list) {
		return list.sptr().size();
	}

	// Counts the number of Objects within a range
	template <typename OsuList>
	int count(const OsuList &list, double lowerBound, double upperBound, bool inclusive = true) {
		int counter = 0;
		auto list_sptr = list.sptr();

		auto condition_excl = [&lowerBound, &upperBound](const auto &sptr) -> bool {
			return ((sptr->offset() > lowerBound) && (sptr->offset() < upperBound));
		};

		auto condition_incl = [&lowerBound, &upperBound](const auto &sptr) -> bool {
			return ((sptr->offset() >= lowerBound) && (sptr->offset() <= upperBound));
		};

		if (inclusive) {
			counter = std::count_if(list_sptr.begin(), list_sptr.end(), condition_incl);
		}
		else {
			counter = std::count_if(list_sptr.begin(), list_sptr.end(), condition_excl);
		}
		return counter;
	}

	// Moves the list by a certain offset
	template <typename OsuList>
	OsuList moveBy(OsuList list, const double moveBy) {
		auto list_sptr = list.sptr();
		for (auto obj : list_sptr) {
			obj->setOffset(obj->offset() + moveBy);
		}

		// This doesn't set the values before returning (error)
		list.derive(list_sptr);
		return list;
	}

	// Moves the list to a certain offset
	// Either the front or the back of the list is used as a reference via the last arg
	template <typename OsuList>
	OsuList moveTo(OsuList list, const double moveTo, bool anchorOnFront = true) {
		auto list_sptr = list.sptr();

		std::vector<double> list_offset = {};
		for (auto obj : list_sptr) {
			list_offset.push_back(obj->offset());
		}

		double move = 0;
		if (anchorOnFront) {
			move = moveTo - *std::min_element(std::begin(list_offset), std::end(list_offset));
		}
		else {
			move = moveTo - *std::max_element(std::begin(list_offset), std::end(list_offset));
		}
		
		return moveBy(list, move);
	}

};

