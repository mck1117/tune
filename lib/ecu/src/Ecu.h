#include <ecu/Ecu.h>

#include "interface/EcuInterface.h"
#include "channels/OutputChannel.h"

#include <map>
#include <thread>

namespace ecu
{
class Ecu final : public IEcu
{
public:
	Ecu(std::unique_ptr<IEcuInterface>&& iface);

	std::shared_ptr<IOutputChannel> FindChannel(const std::string& id) const override;

	void Run();

private:
	void Loop();
	void UpdateOutputChannels();

	std::thread m_updateThread;

	std::unique_ptr<IEcuInterface> m_interface;
	OutputChannelParser m_outputChannelParser;

	std::map<std::string, std::shared_ptr<IOutputChannel>> m_floatOutputChannels;
};
}
