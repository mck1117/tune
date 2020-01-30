#include "imgui_ext.h"

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <algorithm>

constexpr size_t CirclePoints = 64;

constexpr float TickLength = 25;
constexpr float Margin = 10;
constexpr float NeedleTipMargin = 10;

namespace ImGui
{
void RoundGauge(float needleAngle, float diameter, const std::vector<float>& tickAngles)
{
    auto circleColor = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
    auto needleColor = ImColor(160, 30, 30, 255);

    auto window = ImGui::GetCurrentWindow();
    const ImVec2 pos = window->DC.CursorPos;
    const ImVec2 size = ImVec2(diameter, diameter);

    const ImRect bb(pos, pos + size);
    ImGui::ItemSize(bb);
    if (!ImGui::ItemAdd(bb, 0)) return;

    ImVec2 center = pos + (size / 2);

    float radius = diameter / 2 - Margin;
    
    float tickInnerRadius = radius - TickLength;
    
    for (const auto tickAngle : tickAngles)
    {
        ImVec2 tickUnitVector = ImVec2(cosf(tickAngle), sinf(tickAngle));
        ImVec2 tickOuter = center + tickUnitVector * radius;
        ImVec2 tickInner = center + tickUnitVector * tickInnerRadius;
        
        window->DrawList->AddLine(tickInner, tickOuter, circleColor, 1.0f);
    }

    float needleRadius = radius - NeedleTipMargin;

    window->DrawList->AddCircle(center, radius, circleColor, CirclePoints, 2.0f);

    ImVec2 needletip = ImVec2(cosf(needleAngle), sinf(needleAngle));
    needletip = needletip * needleRadius + center;

    window->DrawList->AddLine(center, needletip, needleColor, 4.0f);
}
} // namespace ImGui

