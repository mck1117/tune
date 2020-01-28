#include <ui/Component.h>

#include <imgui.h>
#include <imgui_internal.h>

class StackPanel : public Component
{
public:
    StackPanel(const std::string& name, ComponentList&& children, bool horizontal = false)
        : m_name(name)
        , m_children(std::move(children))
        , m_horizontal(horizontal)
    {
    }
    
protected:
    void Render(IDispatcher& dispatcher) const override
    {
        ImGui::BeginGroup();

        auto prev = ImGui::GetCurrentWindow()->DC.LayoutType;

        ImGui::GetCurrentWindow()->DC.LayoutType = m_horizontal ? ImGuiLayoutType_Horizontal : ImGuiLayoutType_Vertical;

        for (auto& child : m_children)
        {
            child->Render(dispatcher);
        }

        ImGui::GetCurrentWindow()->DC.LayoutType = prev;

        ImGui::EndGroup();
    }
    
private:
    const std::string m_name;
    const std::vector<std::unique_ptr<Component> > m_children;
    const bool m_horizontal;
};


namespace c
{
std::unique_ptr<Component> sp(const std::string& name, ComponentList&& children, bool hor)
{
    return std::make_unique<StackPanel>(name, std::move(children), hor);
}
}
