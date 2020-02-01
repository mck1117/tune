#include "pal/include/SerialPort.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace ecu
{
class WindowsSerialPort : public ISerialPort
{
public:
	WindowsSerialPort(const std::string& portName, uint32_t baudRate)
		: m_portName(portName)
		, m_baudRate(baudRate)
	{
	}

	~WindowsSerialPort()
	{
		CloseHandle(m_port);
	}

	void Open() override
	{
		HANDLE port;
		port = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		// failed to open port
		if (port == INVALID_HANDLE_VALUE) {
			throw std::exception("Failed to open serial port");
		}

		DCB params = { 0 };
		params.DCBlength = sizeof(params);

		GetCommState(port, &params);
		params.BaudRate = m_baudRate;

		// 8 bits, no parity, one stop
		params.ByteSize = 8;
		params.Parity = NOPARITY;
		params.StopBits = ONESTOPBIT;
		bool b = SetCommState(port, &params);

		COMMTIMEOUTS timeout = { 0 };
		timeout.ReadIntervalTimeout = 50;
		timeout.ReadTotalTimeoutConstant = 50;
		timeout.ReadTotalTimeoutMultiplier = 50;
		timeout.WriteTotalTimeoutConstant = 50;
		timeout.WriteTotalTimeoutMultiplier = 10;

		SetCommTimeouts(port, &timeout);

		m_port = port;
	}

	size_t Read(uint8_t* buffer, size_t count) override;

	size_t Send(const uint8_t* buffer, size_t count) override;

private:
	const std::string m_portName;
	const uint32_t m_baudRate;

	HANDLE m_port = 0;
};



size_t WindowsSerialPort::Read(uint8_t* buffer, size_t count)
{
	DWORD read;

	bool ret = ReadFile(m_port, buffer, count, &read, 0);

	return read;
}

size_t WindowsSerialPort::Send(const uint8_t* buffer, size_t count)
{
	DWORD written;

	bool ret = WriteFile(m_port, buffer, count, &written, 0);

	return written;
}


std::unique_ptr<ISerialPort> ISerialPort::Make(const std::string& portName, uint32_t baudRate)
{
	return std::make_unique<WindowsSerialPort>(portName, baudRate);
}
} // namespace ecu
