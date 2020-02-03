#include <Ecu.h>

namespace ecu
{

Ecu::Ecu(std::unique_ptr<IEcuInterface>&& iface)
	: m_interface(std::move(iface))
	, m_outputChannelParser(BuildChannels())
{
	Run();
}

std::vector<OutputChannelBinaryConfiguration> Ecu::BuildChannels()
{
	// temporary for testing!
	auto rpm = std::make_shared<ecu::ScaledOutputChannel<uint16_t>>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 8000 }));
	auto iat = std::make_shared<ecu::ScaledOutputChannel< int16_t>>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 }), 100);
	auto clt = std::make_shared<ecu::ScaledOutputChannel< int16_t>>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  }), 100);
	auto map = std::make_shared<ecu::ScaledOutputChannel<uint16_t>>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 }), 30);
	auto tps = std::make_shared<ecu::ScaledOutputChannel<int16_t>>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 }), 100);

	std::vector<OutputChannelBinaryConfiguration> channels;

	channels.push_back({ rpm, 4 });
	channels.push_back({ iat, 14 });
	channels.push_back({ clt, 12 });
	channels.push_back({ map, 30 });
	channels.push_back({ tps, 20 });

	m_floatOutputChannels.insert({ "rpm", rpm });
	m_floatOutputChannels.insert({ "iat", iat });
	m_floatOutputChannels.insert({ "clt", clt });
	m_floatOutputChannels.insert({ "map", map });
	m_floatOutputChannels.insert({ "tps", tps });

	// todo: this should be passed in as a config, not generated in source
	return channels;
}

void Ecu::Run()
{
	m_updateThread = std::thread([this]() { Loop(); });
}

void Ecu::Loop()
{
	while (true)
	{
		UpdateOutputChannels();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
