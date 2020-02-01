#include <ecu/Ecu.h>

#include "Ecu.h"

#include "pal/include/SerialPort.h"
#include "interface/TunerstudioProtocol.h"

namespace ecu
{
std::shared_ptr<IEcu> IEcu::MakeTunerstudioEcu(const std::string& serialPort, uint32_t baudRate)
{
	auto port = ISerialPort::Make(serialPort, baudRate);

	port->Open();

	// TODO: why doesn't this compile?
	//std::unique_ptr<IEcuTransport> ts = std::make_unique<TunerstudioEcuInterface>(port);
	//return std::make_shared<Ecu>(std::move(ts));

	return std::make_shared<Ecu>(nullptr);
}
}
