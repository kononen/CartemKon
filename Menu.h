#pragma once

#include <vector>
#include "Event.h"


class Menu
{
	public:
	Menu();

	void runMainMenu(std::vector<Event>& queue, bool& runApp, bool& useMultithreading);
};

