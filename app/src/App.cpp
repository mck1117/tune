#include "components/Component.h"
#include "nav/WindowManager.h"
#include "state/RootState.h"

#include <imgui.h>
#include <memory>

std::unique_ptr<Component> myWindow(const RootState& st);

namespace app
{
	void init()
	{
		GetWindowManager()->GetState() = GetInitialState();

		GetWindowManager()->AddWindow(
			[](const RootState& state)
			{
				return myWindow(state);
			}
		);
	}

	void render()
	{
		GetWindowManager()->Render();

		// Extra debugging GUI
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
