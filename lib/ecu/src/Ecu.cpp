
#include <ecu/Ecu.h>

#include <ecu/OutputChannel.h>

#include <map>

namespace ecu
{

class Ecu final : public IEcu
{
    std::shared_ptr<OutputChannelBase> FindChannel(const std::string& id) const override;

private:
    std::map<std::string, std::shared_ptr<FloatOutputChannel>> m_floatOutputChannels;
};

std::shared_ptr<OutputChannelBase> Ecu::FindChannel(const std::string& id) const
{
    auto it = m_floatOutputChannels.find(id);

    if (it != m_floatOutputChannels.end())
    {
        return it->second;
    }

    return nullptr;
}
} // namespace ecu
