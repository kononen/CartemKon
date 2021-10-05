#pragma once

#include <vector>
#include <string>

namespace Globals
{
	const int defaultGenerationMin = 0;
	const int defaultGenerationMax = 0;
	const int defaultSize = 0;

	extern bool runInnitialized;

	const std::vector<std::string> eventNames = { "--close / -c", "--help / -h", "--enable_multithreading / -em",
		"--disable_multithreading / -dm", "--execute_algorythms / -ea" };

	const std::string lineSeparator = "====================";
}
