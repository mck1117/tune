#include "FakeEcu.h"
#include "channels/FakeOutputChannel.h"

namespace ecu
{
FakeEcu::FakeEcu()
{
    // Place a few fake channels for testing
    m_outputChannels.insert({"rpm", std::make_shared<ecu::FakeOutputChannel>("rpm", "RPM", ecu::ChannelBounds<float>({ 0, 6000 }))});
    m_outputChannels.insert({"iat", std::make_shared<ecu::FakeOutputChannel>("rpm", "IAT", ecu::ChannelBounds<float>({ -20, 80 }))});
    m_outputChannels.insert({"clt", std::make_shared<ecu::FakeOutputChannel>("rpm", "CLT", ecu::ChannelBounds<float>({ -20, 120  }))});
    m_outputChannels.insert({"map", std::make_shared<ecu::FakeOutputChannel>("rpm", "MAP", ecu::ChannelBounds<float>({ 0, 250 }))});
    m_outputChannels.insert({"tps", std::make_shared<ecu::FakeOutputChannel>("rpm", "TPS", ecu::ChannelBounds<float>({ 0, 100 }))});

    Run();
}

void FakeEcu::UpdateOutputChannels()
{
    for (auto& ch : m_outputChannels)
    {
        auto ch2 = std::static_pointer_cast<FakeOutputChannel>(ch.second);
        
        ch2->Update();
    }
}
}
