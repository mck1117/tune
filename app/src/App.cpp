#include "components/Component.h"
#include "nav/WindowManager.h"
#include "state/RootState.h"

#include <imgui.h>
#include <memory>

std::unique_ptr<Component> myWindow(const RootState& st);
std::unique_ptr<Component> ecuWindow(const RootState& st);


namespace app
{
	void init()
	{
		GetWindowManager()->GetState() = GetInitialState();

		GetWindowManager()->AddWindow(myWindow);
		GetWindowManager()->AddWindow(ecuWindow);
	}

	void render()
	{
		GetWindowManager()->Render();

		// Extra debugging GUI
        ImGui::ShowMetricsWindow();
	}
}
