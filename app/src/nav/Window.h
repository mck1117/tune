#pragma once

#include <atomic>
#include <memory>
#include <string>

#include "WindowManager.h"
#include "components/Component.h"

struct IDispatcher;
struct Component;

class WindowBase
{
public:
    WindowBase(const std::string& title) : m_title(title) { }
    virtual ~WindowBase() = default;

    bool IsDeleted() { return m_isDeleted; }

    virtual void Render(IDispatcher& dispatcher);
    void Build();

protected:
    virtual std::unique_ptr<Component> BuildImpl() = 0;

    IWindowManager* wm();

private:
    void Delete() { m_isDeleted = true; }

    bool m_isDeleted = false;

    static uintptr_t s_nextId;
    uintptr_t m_id = s_nextId++;

    std::string m_title;
    std::unique_ptr<Component> m_current = nullptr;
};

template <class TState>
class Window : public WindowBase
{
public:
    Window(const std::string& title, const TState& state)
        : WindowBase(title)
        , m_state(state)
    {}

protected:
    virtual std::unique_ptr<Component> BuildImpl(const TState& state) = 0;

    std::unique_ptr<Component> BuildImpl() final override
    {
        return BuildImpl(m_state);
    }

private:
    const TState& m_state;
};
