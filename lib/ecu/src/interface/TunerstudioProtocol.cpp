
#include "TunerstudioProtocol.h"

namespace ecu
{

std::vector<uint8_t> TunerstudioEcuInterface::GetOutputChannelBuffer()
{
	std::vector<uint8_t> cmd{ 0, 5, '0', 0, 0, 0xdc, 0 };

	auto result = m_protocol.DoTransactionCrc(cmd);

	// first byte is status
	result.erase(result.begin());

	return result;
}
}
