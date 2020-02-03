#pragma once

#include "dispatcher/Dispatcher.h"

#include <memory>
#include <vector>
#include <string>

struct IDispatcher;

struct Component
{
    virtual void Render(IDispatcher& dispatcher) const = 0;
    virtual ~Component() = default;
};

using ComponentList = std::vector<std::unique_ptr<Component>>;

// Fwd declares for stuff used below
namespace ecu { struct IOutputChannel; }

namespace c
{
std::unique_ptr<Component> sp(const std::string& name, ComponentList&& children, bool hor = false);
std::unique_ptr<Component> btn(const std::string& t, Callback cb);
std::unique_ptr<Component> tb(const std::string& t);
std::unique_ptr<Component> w(const std::string& title, std::unique_ptr<Component>&& child);
std::unique_ptr<Component> gauge(const std::shared_ptr<const ecu::IOutputChannel>& channel, float minAngle, float maxAngle);
std::unique_ptr<Component> slider(const std::string& label, float value, std::function<Action(float)>&& moved, float min, float max);
std::unique_ptr<Component> chtext(const std::shared_ptr<const ecu::IOutputChannel>& channel);
std::unique_ptr<Component> ti(const std::string& text, std::function<Action(const std::string&)>&& changed);
std::unique_ptr<Component> sep();
}
