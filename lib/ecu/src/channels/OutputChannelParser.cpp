#include <vector>
#include <algorithm>
#include <memory>

#include "OutputChannelParser.h"

namespace ecu
{

static bool CompareBinaryConfigs(const OutputChannelBinaryConfiguration& first, const OutputChannelBinaryConfiguration& second)
{
    return first.Offset < second.Offset;
}

OutputChannelParser::OutputChannelParser(std::vector<OutputChannelBinaryConfiguration>&& channels)
    : m_channels(std::move(channels))
{
    // sort to improve cache locality so we can read sequentially from the input buffer,
    //   and write sequentially to channels
    std::sort(m_channels.begin(), m_channels.end(), CompareBinaryConfigs);
}

void OutputChannelParser::UpdateChannelsFromBuffer(const Span<uint8_t> readBuffer)
{
    for (auto it = m_channels.begin(); it != m_channels.end(); it++)
    {
        auto& channel = *it;
        
        Span<uint8_t> channelBuf;
        
        // end of buffer - not all channels read
        try
        {
            channelBuf = readBuffer.Slice(channel.Offset, channel.Size);
        }
        catch (...)
        {
            // todo
            throw;
        }
        
        // Allow the channel to convert itself (it knows better than we do)
        channel.Channel->PostBytes(channelBuf);
    }
}

} // namespace ecu
