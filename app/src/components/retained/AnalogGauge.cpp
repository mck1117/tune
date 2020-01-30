#include <ui/Component.h>

#include <imgui.h>
#include <ui/imgui_ext.h>

#include <ecu/IOutputChannel.h>

class GaugeAnalog : public Component
{
public:
    GaugeAnalog(const std::shared_ptr<const ecu::IOutputChannel>& channel)
        : m_channel(channel)
        , m_scale(2 * 3.14159f /
                  (m_channel->GetBoundsAsFloat().Max - m_channel->GetBoundsAsFloat().Min))
        , m_add(3.14159f)
    {
        
    }
    
protected:
    void Render(IDispatcher& dispatcher) const override
    {
        float angle = m_channel->GetValueAsFloat() * m_scale + m_add;
        ImGui::RoundGauge(angle, m_size);
    }
    
private:
    const std::shared_ptr<const ecu::IOutputChannel> m_channel;
    
    const float m_scale, m_add;
    
    const float m_size = 150;
};

namespace c
{
std::unique_ptr<Component> gauge(const std::shared_ptr<const ecu::IOutputChannel>& channel)
{
    return std::make_unique<GaugeAnalog>(channel);
}
}
