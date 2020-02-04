#pragma once

#include <memory>

struct RootState;
class WindowBase;

struct IWindowManager
{
    virtual void AddWindow(const std::shared_ptr<WindowBase>& window) = 0;
	virtual RootState& GetState() = 0;
	virtual void Render() = 0;
	virtual void NeedsRender() = 0;

	virtual ~IWindowManager() = default;
};

IWindowManager* GetWindowManager();
