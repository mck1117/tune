#include <memory>

#include "nav/WindowManager.h"

#include <algorithm>

#include "state/RootState.h"

#include "components/Component.h"

#include <ecu/IOutputChannel.h>

using namespace ecu;

Action SetChannelAction(float value)
{
	printf("SetChannelAction %f\n", value);

	return [=](IDispatcher&, RootState& state)
	{
		state.channel->SetValue(value);
	};
}

Action SetGaugeMin(float value)
{
    printf("SetGaugeMin %f\n", value);
    
    return [=](IDispatcher&, RootState& state)
    {
        state.gaugeMin = value;
        GetWindowManager()->NeedsRender();
    };
}

Action SetGaugeMax(float value)
{
    printf("SetGaugeMin %f\n", value);
    
    return [=](IDispatcher&, RootState& state)
    {
        state.gaugeMax = value;
        GetWindowManager()->NeedsRender();
    };
}

Action SearchStringChanged(const std::string& str)
{
	printf("SearchStringChanged %s\n", str.c_str());

	return [=](IDispatcher&, RootState& state)
	{
		state.searchString = str;
        
        if (state.ecu)
        {
            state.channel = state.ecu->FindChannel(str);

			GetWindowManager()->NeedsRender();
		}
	};
}

Action SerialPortChanged(const std::string& str)
{
	printf("SerialPortChanged %s\n", str.c_str());

	return [=](IDispatcher&, RootState& state)
	{
		state.serialPort = str;
	};
}

std::unique_ptr<Component> myWindow(const RootState& st);

Action ConnectPressed()
{
	return [](IDispatcher&, RootState& state)
	{
		state.ecu = IEcu::MakeTunerstudioEcu(state.serialPort, 115200);
        
        // show the main window now that we have an ECU
        GetWindowManager()->AddWindow(myWindow);
		GetWindowManager()->NeedsRender();
	};
};

Action ConnectFakeEcu()
{
    return [](IDispatcher&, RootState& state)
    {
        state.ecu = IEcu::MakeSynthetic();
        
        // show the main window now that we have an ECU
        GetWindowManager()->AddWindow(myWindow);
        GetWindowManager()->NeedsRender();
    };
};

Action DisconnectEcu()
{
    return [](IDispatcher&, RootState& state)
    {
        state.ecu = nullptr;
        GetWindowManager()->NeedsRender();
    };
};

std::unique_ptr<Component> myWindow(const RootState& st)
{
    // if no ECU, destroy this window
    if (!st.ecu) return nullptr;

	ComponentList upper;
	upper.push_back(c::tb("Look for:"));
	upper.push_back(c::ti(st.searchString, [](const std::string& str) { return SearchStringChanged(str); }));

    ComponentList children;
	children.push_back(c::sp("upper", std::move(upper)));

	if (st.channel)
	{
		children.push_back(c::chtext(st.channel));
		children.push_back(c::gauge(st.channel, st.gaugeMin, st.gaugeMax));
		children.push_back(c::slider(
			"Channel value",
			st.channel->GetValueAsFloat(),
			[](float val)
			{
				return SetChannelAction(val);
			}, st.channel->GetBoundsAsFloat().Min, st.channel->GetBoundsAsFloat().Max
        ));
        
        children.push_back(c::slider(
            "Gauge min",
            st.gaugeMin,
            [](float val)
            {
                return SetGaugeMin(val);
            }, -360, 360
        ));
        children.push_back(c::slider(
            "Gauge max",
            st.gaugeMax,
            [](float val)
            {
                return SetGaugeMax(val);
            }, -360, 360
        ));
	}
	else
	{
		children.push_back(c::tb("Channel not found!"));
	}

    return c::w("myWindow", c::sp("mainstack", std::move(children)));
}

std::unique_ptr<Component> ecuWindow(const RootState& st)
{
	ComponentList view;

    if (st.ecu)
    {
        view.push_back(c::btn("Disconnect", []() { return DisconnectEcu(); }));
    }
    else
    {
        view.push_back(c::ti(st.serialPort, [](const std::string& str) { return SerialPortChanged(str); }));
        view.push_back(c::btn("Connect", []() { return ConnectPressed(); }));
        view.push_back(c::btn("Connect fake ECU", []() { return ConnectFakeEcu(); }));
    }

	return c::w("Ecu Connection", c::sp("ms", std::move(view)));
}
