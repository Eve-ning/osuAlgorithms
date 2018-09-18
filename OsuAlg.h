#pragma once
class OsuAlg
{
public:
	OsuAlg() = delete;
	~OsuAlg() = delete;

	// Counts the number of Objects
	template <typename OsuList>
	static int count(const OsuList &list) {
		return list.sptr().size();
	}

	// Counts the number of Objects within a range
	template <class OsuList>
	static int count(const OsuList &list, double lowerBound, double upperBound, bool inclusive = true) {
		int counter = 0;
		auto list_sptr = list.sptr();

		if (inclusive) {
			for (auto obj : list_sptr) {
				if (obj->offset() >= lowerBound && obj->offset() <= upperBound) {
					counter++;
				}
			}
		}
		else {
			for (auto obj : list_sptr) {
				if (obj->offset() > lowerBound && obj->offset() < upperBound) {
					counter++;
				}
			}
		}
		return counter;
	}

};

