#include <ecu/Ecu.h>

#include "Ecu.h"
#include "FakeEcu.h"

#include "pal/include/SerialPort.h"
#include "interface/TunerstudioProtocol.h"

namespace ecu
{
std::shared_ptr<IEcu> IEcu::MakeTunerstudioEcu(const std::string& serialPort, uint32_t baudRate)
{
	auto port = ISerialPort::Make(serialPort, baudRate);

	port->Open();
    
    auto ts = std::make_unique<TunerstudioEcuInterface>(std::move(port));
	return std::make_shared<Ecu>(std::move(ts));
}

std::shared_ptr<IEcu> IEcu::MakeSynthetic()
{
    return std::make_shared<FakeEcu>();
}
}
