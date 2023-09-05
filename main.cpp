#include <iostream>

#include "rt_manager.hpp"

int main()
{
	auto *rt_manager = new RtManager(44100,128);
	for(auto &e : rt_manager->getDeviceList())
	{
		std::cout << e << std::endl;
	}

	uint32_t id;
	std::cin >> id;
	rt_manager->openStream(id);

	rt_manager->startStream();
	char input;
	std::cin.get(input);
	std::cin.get(input);
	rt_manager->stopStream();
}
