
#include "TunerstudioProtocol.h"

enum class TsResponseCode : uint8_t
{
	Ok = 0x00,
	PageData = 0x02,
	ConfigError = 0x03,
	BurnOk = 0x04,

	// errors
	Underrun = 0x80,
	Overrun = 0x81,
	CrcFailure = 0x82,
	UnrecognizedCommand = 0x83,
	OutOfRange = 0x84,
	Busy = 0x85,
	FlashLocked = 0x86,
};

bool IsSuccess(TsResponseCode code)
{
	return code < TsResponseCode::Underrun;
}

namespace ecu
{

std::vector<uint8_t> TunerstudioEcuInterface::GetOutputChannelBuffer()
{
	std::vector<uint8_t> cmd{ 0, 5, 'O', 0, 0, 0xdc, 0 };

	for(int retries = 3; retries > 0; retries--)
	{
		auto result = m_protocol.DoTransactionCrc(cmd);

		auto status = static_cast<TsResponseCode>(result[0]);
		if (IsSuccess(status))
		{
			// Erase status byte
			result.erase(result.begin());
			return result;
		}
	}

	// if we got here, we failed all retries
	// todo: handle properly
	throw "";
}
}
