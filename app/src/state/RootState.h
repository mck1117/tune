#pragma once

#include <ecu/IOutputChannel.h>
#include <ecu/Ecu.h>

#include <map>

struct RootState
{
	// For playing with gauges
	std::string searchString;
	std::shared_ptr<ecu::IOutputChannel> channel;
	std::map<std::string, std::shared_ptr<ecu::IOutputChannel>> demochannels;


	std::string serialPort;
	std::shared_ptr<ecu::IEcu> ecu;

    float gaugeMin, gaugeMax;
};

RootState GetInitialState();
