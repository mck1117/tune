#include "pal/include/SerialPort.h"
#include "pal/unix/UnixSerialPortBase.h"

#include <fcntl.h>
#include <termios.h>

namespace ecu
{
class MacSerialPort : public UnixSerialPortBase
{
public:
	MacSerialPort(const std::string& portName, uint32_t baudRate)
		: m_portName(portName)
		, m_baudRate(baudRate)
	{
	}

	~MacSerialPort()
	{
        if (m_port)
        {
            close(m_port);
        }
	}

	void Open() override
	{
        int fd = open(m_portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

        if (fd == -1)
        {
            // todo: throw
        }

        termios options;
        
        // Open the device in nonblocking mode
        fcntl(fd, F_SETFL, FNDELAY);

        // Set parameters
        tcgetattr(fd, &options);
        bzero(&options, sizeof(options));
        
        cfsetispeed(&options, m_baudRate);
        cfsetospeed(&options, m_baudRate);
        
        options.c_cflag |= ( CLOCAL | CREAD |  CS8);    // Configure the device : 8 bits, no parity, no control
        options.c_iflag |= ( IGNPAR | IGNBRK );
        options.c_cc[VTIME] = 0;                          // Timer unused
        options.c_cc[VMIN] = 0;                           // At least on character before satisfy reading
        tcsetattr(fd, TCSANOW, &options);

		m_port = fd;
	}

private:
	const std::string m_portName;
	const uint32_t m_baudRate;

	int m_port = 0;
};

std::unique_ptr<ISerialPort> ISerialPort::Make(const std::string& portName, uint32_t baudRate)
{
	return std::make_unique<MacSerialPort>(portName, baudRate);
}
} // namespace ecu
