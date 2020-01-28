#include <ui/Component.h>

#include <imgui.h>

class Button final : public Component
{
public:
    Button(const std::string& text, Callback onClick)
        : m_text(text)
        , m_onClick(onClick)
    {
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
        if (ImGui::Button(m_text.c_str()))
        {
            auto c = m_onClick;
            dispatcher.Dispatch(std::move(c));
        }
    }
    
private:
    const std::string m_text;
    const Callback m_onClick;
};

namespace c
{
std::unique_ptr<Component> btn(const std::string& t, Callback cb)
{
    return std::make_unique<Button>(t, cb);
}
}
