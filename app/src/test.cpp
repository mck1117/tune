#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>

#include <imgui.h>
#include <imgui_internal.h>
#include <ui/imgui_ext.h>

#include <ui/WindowManager.h>

#include <algorithm>

#include <ui/RootState.h>

#include <ui/Dispatcher.h>
#include <ui/Component.h>

#include <ecu/OutputChannel.h>

using namespace ecu;


Action SetChannelAction(float value)
{
	printf("SetChannelAction %f\n", value);

	return [=](IDispatcher&, RootState& state)
	{
		state.channel->SetValue(value);
	};
}

Action FindPressed()
{
	return [=](IDispatcher&, RootState& state)
	{
		return;

		printf("FindPressed %s\n", state.searchString.c_str());

		state.channel = state.ecu->FindChannel(state.searchString);
		GetWindowManager()->NeedsRender();
	};
}

Action SearchStringChanged(const std::string& str)
{
	printf("SearchStringChanged %s\n", str.c_str());

	return [=](IDispatcher&, RootState& state)
	{
		state.searchString = str;

		auto ch = state.ecu->FindChannel(str);

		if (ch)
		{
			state.channel = std::move(ch);
			GetWindowManager()->NeedsRender();
		}
	};
}

std::unique_ptr<Component> myWindow(const RootState& st)
{
	ComponentList upper;
	upper.push_back(c::tb("Look for:"));
	upper.push_back(c::ti([](const std::string& str) { return SearchStringChanged(str); }));
	upper.push_back(c::btn("Find", []() { return FindPressed(); }));

    ComponentList children;
	children.push_back(c::sp("upper", std::move(upper)));

	if (st.channel)
	{
		children.push_back(c::chtext(st.channel));
		children.push_back(c::gauge(st.channel));
		children.push_back(c::slider(
			"Test slider",
			st.channel->GetValue(),
			[](float val)
			{
				return SetChannelAction(val);
			}, st.channel->GetBoundsAsFloat().Min, st.channel->GetBoundsAsFloat().Max
				));
	}
	else
	{
		children.push_back(c::tb("Channel not found!"));
	}

    return c::w("myWindow", c::sp("mainstack", std::move(children)));
}

RootState lastState{};

std::unique_ptr<Component> p;

void init()
{
	GetWindowManager()->AddWindow(
		[](const RootState& state)
		{
			return myWindow(state);
		}
		);
}

void render()
{
	static bool hasInit = false;

	if (!hasInit)
	{
		hasInit = true;
		init();
	}

	GetWindowManager()->Render();
}
