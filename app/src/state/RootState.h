#pragma once

#include <ecu/IOutputChannel.h>
#include <ecu/Ecu.h>

struct RootState
{
	std::string searchString;
	std::shared_ptr<ecu::IEcu> ecu;
	std::shared_ptr<ecu::IOutputChannel> channel;
};

RootState GetInitialState();
