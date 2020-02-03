#include <ecu/Ecu.h>

#include "interface/EcuInterface.h"
#include "channels/OutputChannel.h"
#include "channels/OutputChannelParser.h"

#include <map>
#include <thread>

namespace ecu
{
class EcuBase : public IEcu
{
protected:
	virtual void UpdateOutputChannels() = 0;

	void Run();

private:
	void Loop();

	std::thread m_updateThread;
};

class Ecu final : public EcuBase
{
public:
	Ecu(std::unique_ptr<IEcuInterface>&& iface);

	std::shared_ptr<IOutputChannel> FindChannel(const std::string& id) const override;

protected:
	void UpdateOutputChannels() override;

private:
	std::vector<OutputChannelBinaryConfiguration> BuildChannels();


	std::unique_ptr<IEcuInterface> m_interface;
	OutputChannelParser m_outputChannelParser;

	std::map<std::string, std::shared_ptr<IOutputChannel>> m_floatOutputChannels;
};
}
