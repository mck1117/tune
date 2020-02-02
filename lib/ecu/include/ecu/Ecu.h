#pragma once

#include <memory>
#include <string>

#include <ecu/IOutputChannel.h>

namespace ecu
{

class FloatOutputChannel;
struct OutputChannelBase;

struct IEcu
{
    virtual std::shared_ptr<ecu::IOutputChannel> FindChannel(const std::string& id) const = 0;

	static std::shared_ptr<IEcu> MakeTunerstudioEcu(const std::string& serialPort, uint32_t baudRate);

	virtual ~IEcu() = default;
};

} // namespace ecu
