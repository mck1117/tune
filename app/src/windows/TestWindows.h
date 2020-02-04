#include "nav/Window.h"

#include <memory>

struct EcuWindow : public Window<RootState>
{
    EcuWindow(const RootState& state);
    std::unique_ptr<Component> BuildImpl(const RootState&) override;
};

struct SingleGaugeDemoWindow : public Window<RootState>
{
    SingleGaugeDemoWindow(const RootState& state);
    std::unique_ptr<Component> BuildImpl(const RootState&) override;
};

struct GaugeListWindow : public Window<RootState>
{
    GaugeListWindow(const RootState& state);
    std::unique_ptr<Component> BuildImpl(const RootState&) override;
};
