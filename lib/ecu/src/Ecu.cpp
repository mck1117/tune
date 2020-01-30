
#include <ecu/Ecu.h>

#include <ecu/OutputChannel.h>

#include <map>

namespace ecu
{

class Ecu final : public IEcu
{
public:
	Ecu()
	{
		// temporary for testing!
		m_floatOutputChannels.insert({"rpm", std::make_shared<ecu::FloatOutputChannel>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 8000 }))});
		m_floatOutputChannels.insert({"iat", std::make_shared<ecu::FloatOutputChannel>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 }))});
		m_floatOutputChannels.insert({"clt", std::make_shared<ecu::FloatOutputChannel>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  }))});
		m_floatOutputChannels.insert({"map", std::make_shared<ecu::FloatOutputChannel>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 }))});
		m_floatOutputChannels.insert({"tps", std::make_shared<ecu::FloatOutputChannel>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 }))});
	}

    std::shared_ptr<FloatOutputChannel> FindChannel(const std::string& id) const override;

private:
    std::map<std::string, std::shared_ptr<FloatOutputChannel>> m_floatOutputChannels;
};

std::shared_ptr<FloatOutputChannel> Ecu::FindChannel(const std::string& id) const
{
    auto it = m_floatOutputChannels.find(id);

    if (it != m_floatOutputChannels.end())
    {
        return it->second;
    }

    return nullptr;
}

std::shared_ptr<IEcu> IEcu::Make()
{
	return std::make_shared<Ecu>();
}

} // namespace ecu
