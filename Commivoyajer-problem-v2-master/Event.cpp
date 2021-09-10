#include "Event.h"

Event::Event()
{
}

Event::Event(std::function<void()> inputFunction)
{
	this->cachedFunction = inputFunction;
}

void Event::executeEvent()
{
	cachedFunction();
}