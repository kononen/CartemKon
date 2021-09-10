#include "App.h"

#include <iostream>
#include "Timer.h"
#include "Globals.h"

#include <thread>
#include <future>

#include <mutex>

std::mutex lock;

App::App()
{
	queue.push_back(Event([=]() {
		Menu* menu = new Menu();
		menu_->runMainMenu(queue, runApp, useMultithreading);
		}) );

	auto f = [=]()
	{ 
		clock_t begin = clock();
		if (useMultithreading)
		{
			std::cout << "threads are running: 2" << std::endl;
			std::promise<int> promiseObj;
			std::future<int> futureObj = promiseObj.get_future();

			std::thread th([=, &promiseObj]()
				{
					if (queue.size() > 1)
					{
						lock.lock();
						auto function = queue[1];
						lock.unlock();

						function.executeEvent();

						lock.lock();
						queue.erase(queue.begin(), queue.begin() + 2);
						lock.unlock();

						promiseObj.set_value(0);
					}
				});

			th.detach();

			run_();

			futureObj.get();
		}
		else
		{
			std::cout << "threads are running: 1" << std::endl;
			run_();

			if (queue.size() > 0)
			{
				queue.erase(queue.begin());
			}
		}
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Execution time: " << elapsed_secs << std::endl << std::endl;
	};

	while (runApp)
	{
		Timer t{ 10, f };
	}
	std::cout << Globals::lineSeparator << std::endl << "End of events" << std::endl;
}

void App::run_()
{
	if (queue.size() > 0)
	{
		lock.lock();
		auto function = queue[0];
		lock.unlock();
		function.executeEvent();
	}
}
