#include <ecu/Ecu.h>

#include "interface/EcuInterface.h"
#include "channels/OutputChannel.h"

#include <map>

namespace ecu
{
class Ecu final : public IEcu
{
public:
	Ecu(std::unique_ptr<IEcuInterface>&& iface);

	std::shared_ptr<IOutputChannel> FindChannel(const std::string& id) const override;

private:
	std::unique_ptr<IEcuInterface> m_interface;

	std::map<std::string, std::shared_ptr<IOutputChannel>> m_floatOutputChannels;
};
}
