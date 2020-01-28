#pragma once

#include <functional>

struct IDispatcher;
struct RootState;
RootState& GetRootState();

// An action to be run on the dispatcher that can mutate state.
using Action = std::function<void(IDispatcher&, RootState&)>;
using Callback = std::function<Action()>;

// Binds an action to its parameter(s), so it can be run by the dispatcher.
template <class TArg>
Action ab(std::function<void(IDispatcher&, RootState&, TArg)> f, TArg arg)
{
    using namespace std::placeholders;
    return std::bind(f, _1, _2, arg);
}

template <class TArg1, class TArg2>
Action ab(std::function<void(IDispatcher&, RootState&, TArg1, TArg2)> f, TArg1 arg1, TArg2 arg2)
{
    using namespace std::placeholders;
    return std::bind(f, _1, _2, arg1, arg2);
}

template <class TArg1, class TArg2, class TArg3>
Action ab(std::function<void(IDispatcher&, RootState&, TArg1, TArg2, TArg3)> f, TArg1 arg1, TArg2 arg2, TArg3 arg3)
{
    using namespace std::placeholders;
    return std::bind(f, _1, _2, arg1, arg2, arg3);
}

struct IDispatcher
{
    // Dispatch a callback, and run the resulting action.
    virtual void Dispatch(Callback&& func) = 0;
    virtual ~IDispatcher() = default;
};

std::shared_ptr<IDispatcher> GetDispatcherInstance();
