#pragma once

#include <memory>
#include <string>

namespace ecu
{

class FloatOutputChannel;
struct OutputChannelBase;

struct IEcu
{
    virtual std::shared_ptr<ecu::FloatOutputChannel> FindChannel(const std::string& id) const = 0;

	static std::shared_ptr<IEcu> Make();

};

} // namespace ecu
