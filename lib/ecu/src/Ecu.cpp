#include <Ecu.h>

namespace ecu
{

Ecu::Ecu(std::unique_ptr<IEcuInterface>&& iface)
	: m_interface(std::move(iface))
	, m_outputChannelParser(BuildChannels())
{
	// temporary for testing!
	m_floatOutputChannels.insert({"rpm", std::make_shared<ecu::FloatOutputChannel>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 8000 }))});
	m_floatOutputChannels.insert({"iat", std::make_shared<ecu::FloatOutputChannel>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 }))});
	m_floatOutputChannels.insert({"clt", std::make_shared<ecu::FloatOutputChannel>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  }))});
	m_floatOutputChannels.insert({"map", std::make_shared<ecu::FloatOutputChannel>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 }))});
	m_floatOutputChannels.insert({"tps", std::make_shared<ecu::FloatOutputChannel>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 }))});

	Run();
}


std::vector<OutputChannelBinaryConfiguration> Ecu::BuildChannels()
{
	// todo: this should be passed in as a config, not generated in source
	return {};
}


void EcuBase::Run()
{
	m_updateThread = std::thread([this]() { Loop(); });
}

void EcuBase::Loop()
{
	while (true)
	{
		UpdateOutputChannels();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
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

	m_outputChannelParser.UpdateChannelsFromBuffer(Span<uint8_t>(och.data(), och.size()));
}

std::map<std::string, std::shared_ptr<IOutputChannel>> GetDemoChannels()
{
	std::map<std::string, std::shared_ptr<IOutputChannel>> map;

	map.insert({ "rpm", std::make_shared<ecu::FloatOutputChannel>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 8000 })) });
	map.insert({ "iat", std::make_shared<ecu::FloatOutputChannel>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 })) });
	map.insert({ "clt", std::make_shared<ecu::FloatOutputChannel>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  })) });
	map.insert({ "map", std::make_shared<ecu::FloatOutputChannel>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 })) });
	map.insert({ "tps", std::make_shared<ecu::FloatOutputChannel>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 })) });

	return map;
}

} // namespace ecu
