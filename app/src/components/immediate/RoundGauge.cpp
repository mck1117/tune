
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <algorithm>

namespace ImGui
{
void RoundGauge(float needleAngle, float size)
{
    auto circleColor = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
    auto needleColor = ImColor(160, 30, 30, 255);

    auto window = ImGui::GetCurrentWindow();
    const ImVec2 pos = window->DC.CursorPos;
    const ImVec2 sz = ImVec2(size, size);

    const ImRect bb(pos, pos + sz);
    ImGui::ItemSize(bb);
    if (!ImGui::ItemAdd(bb, 0)) return;

    ImVec2 center = pos + (sz / 2);

    float radius = std::min(sz.x / 2, sz.y / 2) - 10;

    float needleRadius = radius - 10;

    window->DrawList->AddCircle(center, radius, circleColor, 50, 10.0f);

    ImVec2 needletip = ImVec2(-sin(needleAngle), cos(needleAngle));
    needletip = needletip * needleRadius + center;

    window->DrawList->AddLine(center, needletip, needleColor, 4.0f);
}
} // namespace ImGui

