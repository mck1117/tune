#pragma once

#include <map>
#include <memory>
#include <string>

namespace ecu
{

struct IOutputChannel;

struct IEcu
{
    virtual std::shared_ptr<ecu::IOutputChannel> FindChannel(const std::string& id) const = 0;
	virtual const std::map<std::string, std::shared_ptr<ecu::IOutputChannel>>& GetChannels() const = 0;

	static std::shared_ptr<IEcu> MakeTunerstudioEcu(const std::string& serialPort, uint32_t baudRate);
	static std::shared_ptr<IEcu> MakeSynthetic();

	virtual ~IEcu() = default;
};

std::map<std::string, std::shared_ptr<IOutputChannel>> GetDemoChannels();

} // namespace ecu
