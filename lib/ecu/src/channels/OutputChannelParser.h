#pragma once

#include "OutputChannel.h"

#include <vector>
#include <memory>

namespace ecu
{
struct OutputChannelBinaryConfiguration
{
    std::shared_ptr<OutputChannelBase> Channel;
    size_t Offset;
    size_t Size;
};

class OutputChannelParser
{
public:
    OutputChannelParser(std::vector<OutputChannelBinaryConfiguration>&& channels);

    void UpdateChannelsFromBuffer(const Span<uint8_t> readBuffer);

private:
    std::vector<OutputChannelBinaryConfiguration> m_channels;
};
}
