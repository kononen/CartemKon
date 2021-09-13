#pragma once

#include <functional>

class Event
{
	public:
		std::function<void()> cachedFunction = []() { return 0; };

		Event();
		Event(std::function<void()> inputFunction);

		void executeEvent();
};

