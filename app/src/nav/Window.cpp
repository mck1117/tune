#include "Window.h"

#include <imgui.h>

#include "components/Component.h"

/*static*/ uintptr_t WindowBase::s_nextId = 0;

void WindowBase::Render(IDispatcher& dispatcher)
{
    if (!m_current)
    {
        return;
    }

    // Unique ID prevents us from stomping windows with the same name but diffent contents
    ImGui::PushID(m_id);

    if (ImGui::Begin(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
    {
        m_current->Render(dispatcher);
    }

    ImGui::End();
    ImGui::PopID();
}

void WindowBase::Build()
{
    auto current = BuildImpl();

    if (!current)
    {
        Delete();
    }
    else
    {
        m_current = std::move(current);
    }
}
