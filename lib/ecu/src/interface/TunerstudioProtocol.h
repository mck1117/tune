
#pragma once

#include <vector>
#include <memory>
#include <cstddef>

#include "EcuInterface.h"
#include "pal/include/SerialPort.h"

namespace ecu
{

class TunerstudioProtocol
{
public:
	explicit TunerstudioProtocol(std::unique_ptr<IEcuTransport>&& port) : m_port(std::move(port)) {}

	std::vector<uint8_t> CrcCommand(char command);
	std::vector<uint8_t> DoTransactionCrc(std::vector<uint8_t>& command);
private:
	void WriteCrcPacket(std::vector<uint8_t>& data);
	std::vector<uint8_t> ReadCrcPacket();

private:
	std::unique_ptr<IEcuTransport> m_port;
};

class TunerstudioEcuInterface : public IEcuInterface
{
public:
	TunerstudioEcuInterface(std::unique_ptr<IEcuTransport>&& transport)
		: m_protocol(std::move(transport)) {}

	std::vector<uint8_t> GetOutputChannelBuffer() override;

private:
	TunerstudioProtocol m_protocol;
};
}
