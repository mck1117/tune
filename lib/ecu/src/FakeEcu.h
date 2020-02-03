#pragma once

#include "Ecu.h"

namespace ecu
{
class FakeEcu final : public EcuBase
{
public:
    FakeEcu();

protected:
    void UpdateOutputChannels() override;
};
}
