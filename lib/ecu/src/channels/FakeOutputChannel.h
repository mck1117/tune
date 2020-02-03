#pragma once

#include "OutputChannel.h"

#include <random>

namespace ecu
{
class FakeOutputChannel final : public ScalarOutputChannel<float>
{
public:
    FakeOutputChannel(const std::string& id, const std::string& displayName, ChannelBounds<float> bounds);

    void Update();

    // todo: should this exist, or should we inherit from a different base?
    void PostBytes(Span<uint8_t>) override {}
private:
    const float m_amplitude, m_center;
    const float m_phaseStep;
    float m_phase = 0;
};
}
