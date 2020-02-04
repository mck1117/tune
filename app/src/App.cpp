
#include "state/RootState.h"
#include "windows/TestWindows.h"

#include <imgui.h>
#include <memory>

std::unique_ptr<Component> myWindow(const RootState& st);
std::unique_ptr<Component> ecuWindow(const RootState& st);

IWindowManager* wm = GetWindowManager();

namespace app
{
	void init()
	{
		GetWindowManager()->AddWindow(std::make_shared<EcuWindow>());
	}

	void render()
	{
		GetWindowManager()->Render();

		// Extra debugging GUI
        ImGui::ShowMetricsWindow();
	}
}
