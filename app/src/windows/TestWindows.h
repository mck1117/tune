#include "nav/Window.h"

#include <memory>

struct EcuWindow : public Window
{
    EcuWindow();
    std::unique_ptr<Component> BuildImpl() override;
};

struct SingleGaugeDemoWindow : public Window
{
    SingleGaugeDemoWindow();
    std::unique_ptr<Component> BuildImpl() override;
};

struct GaugeListWindow : public Window
{
    GaugeListWindow();
    std::unique_ptr<Component> BuildImpl() override;
};
