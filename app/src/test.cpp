#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>

#include <imgui.h>
#include <imgui_internal.h>
#include <ui/imgui_ext.h>


#include <algorithm>

#include <ui/Dispatcher.h>
#include <ui/Component.h>

#include <ecu/OutputChannel.h>

using namespace ecu;

struct RootState
{
    std::shared_ptr<FloatOutputChannel> channel = std::make_shared<FloatOutputChannel>("test", "Test Channel", ChannelBounds<float>({0, 300}));
};

RootState state;

RootState& GetRootState()
{
    return state;
}

void SetChannelAction(IDispatcher&, RootState& state, float value)
{
    state.channel->SetValue(value);
}

std::unique_ptr<Component> myWindow(const std::string& title, const RootState& st)
{
    ComponentList children;
    children.push_back(c::chtext(st.channel));
    children.push_back(c::gauge(st.channel));
    children.push_back(c::slider(
        "Test slider",
        st.channel->GetValue(),
        [] (float val)
        {
            return ab<float>(SetChannelAction, val);
        }, st.channel->GetBoundsAsFloat().Min, st.channel->GetBoundsAsFloat().Max
    ));

    return c::w(title, c::sp("mainstack", std::move(children)));
}

RootState lastState{};

std::unique_ptr<Component> p;

std::shared_ptr<IDispatcher> d = GetDispatcherInstance();

void render()
{
    if (!p )//|| lastState.value != state.value)
    {
        p = myWindow("w1", state);
        lastState = state;
    }
    
    p->Render(*d);
}
