#pragma once

#include <ecu/IOutputChannel.h>
#include <ecu/Ecu.h>

struct RootState
{
	std::string searchString;
	std::shared_ptr<ecu::IOutputChannel> channel;

	std::string serialPort;
	std::shared_ptr<ecu::IEcu> ecu;

    float gaugeMin, gaugeMax;
};

RootState GetInitialState();
