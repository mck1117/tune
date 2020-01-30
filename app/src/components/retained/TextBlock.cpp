#include "components/Component.h"

#include <imgui.h>

class TextBlock final : public Component
{
public:
    TextBlock(const std::string& text)
        : m_text(text)
    {
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
        ImGui::TextUnformatted(m_text.c_str());
    }

private:
    const std::string m_text;
};

namespace c
{
std::unique_ptr<Component> tb(const std::string& t)
{
    return std::make_unique<TextBlock>(t);
}
}
