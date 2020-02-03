#include "FakeOutputChannel.h"

#include <random>

static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_real_distribution<> dist(0.002f, 0.02f);

namespace ecu
{
FakeOutputChannel::FakeOutputChannel(const std::string& id, const std::string& displayName, ChannelBounds<float> bounds)
    : ScalarOutputChannel<float>(id, displayName, bounds)
    , m_amplitude((bounds.Max - bounds.Min) / 2)
    , m_center((bounds.Max + bounds.Min) / 2)
    , m_phaseStep(dist(rng))
{
}

void FakeOutputChannel::Update()
{
    m_phase += m_phaseStep;
    
    SetValue(sinf(m_phase) * m_amplitude + m_center);
}
}
