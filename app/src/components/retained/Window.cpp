#include <ui/Component.h>

#include <imgui.h>

class Window final : public Component
{
public:
    Window(const std::string& name, std::unique_ptr<Component> child)
        : m_child(std::move(child))
        , m_name(name)
    {
    }
    
public:
    void Render(IDispatcher& dispatcher) const override
    {
        ImGui::Begin(m_name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

        if(m_child)
        {
            m_child->Render(dispatcher);
        }
        
        ImGui::End();
    }

private:
    std::unique_ptr<Component> m_child;
    std::string m_name;
};

namespace c
{
std::unique_ptr<Component> w(const std::string& title, std::unique_ptr<Component>&& child)
{
    return std::make_unique<Window>(title, std::move(child));
}
}
