#pragma once

#include <ecu/IOutputChannel.h>
#include <ecu/Ecu.h>

#include <map>

struct RootState
{
	// Single gauge inspector
	std::string searchString;
	std::shared_ptr<ecu::IOutputChannel> channel = nullptr;

	std::string serialPort;
	std::shared_ptr<ecu::IEcu> ecu = nullptr;

    float gaugeMin, gaugeMax;
};

RootState GetInitialState();
