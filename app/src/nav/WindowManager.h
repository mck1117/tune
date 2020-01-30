#pragma once

#include <functional>
#include "components/Component.h"

struct RootState;

struct IWindowManager
{
    virtual void AddWindow(std::function<std::unique_ptr<Component>(const RootState&)> render) = 0;
	virtual RootState& GetState() = 0;
	virtual void Render() = 0;
	virtual void NeedsRender() = 0;
};

IWindowManager* GetWindowManager();
