#pragma once

#include <ecu/OutputChannel.h>
#include <ecu/Ecu.h>

struct RootState
{
	std::string searchString;
	std::shared_ptr <ecu::IEcu> ecu = ecu::IEcu::Make();
	std::shared_ptr<ecu::FloatOutputChannel> channel;
};
