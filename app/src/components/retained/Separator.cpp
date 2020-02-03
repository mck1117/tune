#include "components/Component.h"

#include <imgui.h>

struct Separator final : public Component
{
    void Render(IDispatcher& dispatcher) const override
    {
        ImGui::Separator();
    }
};

namespace c
{
std::unique_ptr<Component> sep()
{
    return std::make_unique<Separator>();
}
}
