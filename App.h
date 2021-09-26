#pragma once

#include "Menu.h"

class App
{
	public:
		bool runApp = true;
		bool useMultithreading = false;

		std::vector<Event> queue;

		App();

	private:
		Menu* menu_ = nullptr;
		void run_();
};

