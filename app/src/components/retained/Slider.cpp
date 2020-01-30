#include "components/Component.h"

#include <imgui.h>
#include <imgui_internal.h>

class Slider final : public Component
{
public:
    Slider(const std::string& label, float value, std::function<Action(float)>&& moved, float min, float max)
        : m_label(label)
        , m_min(min)
        , m_max(max)
        , m_moved(std::move(moved))
        , m_lastVal(value)
    {
    }
    
protected:
    void Render(IDispatcher& dispatcher) const override
    {
        float val = m_lastVal;
        
        ImGui::SliderFloat(m_label.c_str(), &val, m_min, m_max);
        
        if (val != m_lastVal)
        {
            auto moved = m_moved;
            dispatcher.Dispatch([moved, val]() { return moved(val); });
            m_lastVal = val;
        }
    }
    
private:
    const std::string m_label;
    
    const float m_min, m_max;
    
    std::function<Action(float)> m_moved;
    
    mutable float m_lastVal;
};

namespace c
{
std::unique_ptr<Component> slider(const std::string& label, float value, std::function<Action(float)>&& moved, float min, float max)
{
    return std::make_unique<Slider>(label, value, std::move(moved), min, max);
}
}
