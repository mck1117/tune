#pragma once

#include <functional>
#include <memory>

struct IDispatcher;
struct RootState;
RootState& GetRootState();

// An action to be run on the dispatcher that can mutate state.
using Action = std::function<void(IDispatcher&, RootState&)>;
using Callback = std::function<Action()>;

struct IDispatcher
{
    // Dispatch a callback, and run the resulting action.
    virtual void Dispatch(Callback&& func) = 0;
    virtual ~IDispatcher() = default;
};

std::shared_ptr<IDispatcher> GetDispatcherInstance();
