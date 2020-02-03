#include "FakeOutputChannel.h"

namespace ecu
{
FakeOutputChannel::FakeOutputChannel(const std::string& id, const std::string& displayName, ChannelBounds<float> bounds)
    : ScalarOutputChannel<float>(id, displayName, bounds)
    , m_amplitude((bounds.Max - bounds.Min) / 2)
    , m_center((bounds.Max + bounds.Min) / 2)
{
}

void FakeOutputChannel::Update()
{
    m_phase += 0.01f;
    
    SetValue(sinf(m_phase) * m_amplitude + m_center);
}
}
