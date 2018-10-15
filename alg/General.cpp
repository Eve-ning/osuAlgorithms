#include "pch.h"
#include "../pch.h"
#include "General.h"

// Concatenates vector to a string with a 1-char delimeter
std::string General::makeCSVHeader(std::vector<std::string> headers, std::string delimeter) {
	std::string output = {};
	for (auto header : headers) {
		output.append(header);
		output.append(delimeter);
	}

	// Remove last comma
	output.pop_back();

	return output;
}
