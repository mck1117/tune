#include "pal/include/SerialPort.h"

namespace ecu
{
std::unique_ptr<ISerialPort> ISerialPort::Make(const std::string& portName, uint32_t baudRate)
{
	return {};
}
}
