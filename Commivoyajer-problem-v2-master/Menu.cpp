#include "Menu.h"

#include <iostream>
#include "Globals.h"

Menu::Menu()
{
}

void Menu::runMainMenu(std::vector<Event>& queue, bool& runApp, bool& useMultithreading)
{
	std::string inpString;
	
	if (!Globals::runInnitialized)
	{
		std::cout << "Enter command. For list of commands enter '--help or -h'" << std::endl;
		Globals::runInnitialized = true;
	}

	std::cin >> inpString;

	if ((inpString == "--close") || (inpString == "-c"))
	{
		if (useMultithreading)
		{
			queue.insert(queue.begin() + 2, (Event([&runApp]() { runApp = false; })));
		}
		else
		{
			queue.insert(queue.begin() + 1, (Event([&runApp]() { runApp = false; })));
		}
	}
	else if ((inpString == "--help") || (inpString == "-h"))
	{
		for (int i = 0; i < Globals::eventNames.size(); i++)
		{
			std::cout << i + 1 << ": " << Globals::eventNames[i] << std::endl;
		}
	}
	else if ((inpString == "--enable_multithreading") || (inpString == "-em"))
	{
		if (!useMultithreading)
		{
			queue.insert(queue.begin() + 1, Event([&useMultithreading]() {useMultithreading = true; std::cout << "Multithreading enabled" << std::endl; }));
		}
	}
	else if ((inpString == "--disable_multithreading") || (inpString == "-dm"))
	{
		if (useMultithreading)
		{
			queue.insert(queue.begin() + 1, Event([&useMultithreading]() {useMultithreading = false; std::cout << "Multithreading disabled" << std::endl; }));
			queue.insert(queue.begin() + 1, Event([]() {std::cout << "Dummy function has been executed" << std::endl; }));
		}
	}
	else if ((inpString == "--execute_algorythms") || (inpString == "-ea"))
	{
		//BNB algotithm: {}
		queue.push_back(Event([]() {}));//queue.push_back(Algjritm1(0,100,5)); B&B method, минимальное расстояние между городами ноль, максимальное 100, всего городов 5 
		//Taboo search BnB: {} 
		queue.push_back(Event([]() {}));//queue.push_back(Algjritm2(0,100,5)); Taboo method 
	}
	else
	{
		std::cout << "No such command: " << inpString << std::endl;
	}

	queue.push_back(Event([]() {std::cout << "Dummy function has been executed" << std::endl; }));
	queue.push_back(Event([&queue, &runApp, this, &useMultithreading]() { runMainMenu(queue, runApp, useMultithreading); }));
}
