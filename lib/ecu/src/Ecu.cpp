#include <Ecu.h>

namespace ecu
{

Ecu::Ecu(std::unique_ptr<IEcuInterface>&& iface)
	: m_interface(std::move(iface))
{
	// temporary for testing!
	m_floatOutputChannels.insert({"rpm", std::make_shared<ecu::FloatOutputChannel>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 8000 }))});
	m_floatOutputChannels.insert({"iat", std::make_shared<ecu::FloatOutputChannel>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 }))});
	m_floatOutputChannels.insert({"clt", std::make_shared<ecu::FloatOutputChannel>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  }))});
	m_floatOutputChannels.insert({"map", std::make_shared<ecu::FloatOutputChannel>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 }))});
	m_floatOutputChannels.insert({"tps", std::make_shared<ecu::FloatOutputChannel>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 }))});
}

std::shared_ptr<IOutputChannel> Ecu::FindChannel(const std::string& id) const
{
    auto it = m_floatOutputChannels.find(id);

    if (it != m_floatOutputChannels.end())
    {
        return it->second;
    }

    return nullptr;
}

void Ecu::UpdateOutputChannels()
{
	auto och = m_interface->GetOutputChannelBuffer();
}

} // namespace ecu
