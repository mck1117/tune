
#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <string>

namespace ecu
{
struct IEcuTransport
{
	virtual size_t Read(uint8_t* buffer, size_t count) = 0;
	virtual size_t Send(const uint8_t* buffer, size_t count) = 0;

	virtual ~IEcuTransport() = default;
};

struct ISerialPort : public IEcuTransport
{
	virtual void Open() = 0;
	
    static std::unique_ptr<ISerialPort> Make(const std::string& portName, uint32_t baudRate);
};
}
