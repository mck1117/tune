#pragma once

#include <atomic>
#include <memory>
#include <string>

#include "WindowManager.h"
#include "components/Component.h"

struct IDispatcher;
struct Component;

class Window
{
public:
    Window(const std::string& title) : m_title(title) { }
    virtual ~Window() = default;

    bool IsDeleted() { return m_isDeleted; }

    void Render(IDispatcher& dispatcher);
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
