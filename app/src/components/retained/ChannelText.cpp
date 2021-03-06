#include "components/Component.h"
#include <ecu/IOutputChannel.h>

#include <imgui.h>

class ChannelText final : public Component
{
public:
    ChannelText(const std::shared_ptr<const ecu::IOutputChannel>& channel, int precision = 2)
        : m_channel(std::move(channel))
        , m_precision(precision)
    {
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
        ImGui::TextUnformatted(m_channel->GetDisplayName().c_str());
        ImGui::SameLine();
        ImGui::TextUnformatted(std::to_string(m_channel->GetValueAsFloat()).c_str());
    }

private:
    const std::shared_ptr<const ecu::IOutputChannel> m_channel;
    const int m_precision;
};




namespace c
{
std::unique_ptr<Component> chtext(const std::shared_ptr<const ecu::IOutputChannel>& channel)
{
    return std::make_unique<ChannelText>(channel);
}
}
