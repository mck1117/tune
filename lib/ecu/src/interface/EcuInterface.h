#pragma once

#include <vector>

namespace ecu
{
struct IEcuInterface
{
	virtual std::vector<uint8_t> GetOutputChannelBuffer() = 0;

	virtual ~IEcuInterface() = default;
};
}
