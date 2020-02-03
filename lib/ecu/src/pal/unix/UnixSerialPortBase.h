#pragma once

#include <cstdint>
#include <cstddef>
#include <unistd.h>

namespace ecu
{
class UnixSerialPortBase : public ISerialPort
{
public:
	virtual ~UnixSerialPortBase()
	{
        if (m_port)
        {
            close(m_port);
        }
	}

	size_t Read(uint8_t* buffer, size_t count) override;

	size_t Send(const uint8_t* buffer, size_t count) override;

protected:
	int m_port = 0;
};

size_t UnixSerialPortBase::Read(uint8_t* buffer, size_t count)
{
    return read(m_port, buffer, count);
}

size_t UnixSerialPortBase::Send(const uint8_t* buffer, size_t count)
{
    return write(m_port, buffer, count);
}
}