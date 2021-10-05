#include "FrizeStep.h"
#include <iostream>
#include "Globals.h"

void FrizeStep::SwapActive(FrizeStep& newActive)
{
	newActive.active = true;
	this->active = false;
}