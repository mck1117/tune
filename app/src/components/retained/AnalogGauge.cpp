#include "components/Component.h"

#include <imgui.h>
#include <imgui_internal.h>
#include "components/immediate/imgui_ext.h"

#include <ecu/IOutputChannel.h>

class GaugeAnalog : public Component
{
public:
    GaugeAnalog(const std::shared_ptr<const ecu::IOutputChannel>& channel, float minAngle, float maxAngle)
        : m_channel(channel)
        , m_scale((maxAngle - minAngle) / (m_channel->GetBoundsAsFloat().Max - m_channel->GetBoundsAsFloat().Min))
        , m_add(minAngle - m_channel->GetBoundsAsFloat().Min * m_scale)
    {
        size_t count = 11;
        float step = (maxAngle - minAngle) / (count - 1);
        
        float x = minAngle;
        
        for (size_t i = 0; i < count; i++) {
            m_ticks.push_back(x);
            x += step;
        }
    }
    
protected:
    void Render(IDispatcher& dispatcher) const override
    {
        float angle = m_channel->GetValueAsFloat() * m_scale + m_add;
        
        ImGui::RoundGauge(angle, m_size, m_ticks);
    }
    
private:
    const std::shared_ptr<const ecu::IOutputChannel> m_channel;
    
    const float m_scale, m_add;
    
    const float m_size = 250;
    
    std::vector<float> m_ticks;
};

namespace c
{
std::unique_ptr<Component> gauge(const std::shared_ptr<const ecu::IOutputChannel>& channel, float minAngle, float maxAngle)
{
    return std::make_unique<GaugeAnalog>(channel, IM_PI * minAngle / 180, IM_PI * maxAngle / 180);
}
}
