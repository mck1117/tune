#include <ecu/OutputChannel.h>
#include <vector>
#include <algorithm>
#include <memory>

namespace ecu
{
struct OutputChannelBinaryConfiguration
{
    const std::shared_ptr<OutputChannelBase> Channel;
    const size_t Offset;
    const size_t Size;
};

static bool CompareBinaryConfigs(const std::shared_ptr<OutputChannelBinaryConfiguration>& first, const std::shared_ptr<OutputChannelBinaryConfiguration>& second)
{
    return first->Offset < second->Offset;
}

class OutputChannelParser
{
public:
    OutputChannelParser(std::vector<std::shared_ptr<OutputChannelBinaryConfiguration>>&& channels)
        : m_channels(std::move(channels))
    {
        std::sort(m_channels.begin(), m_channels.end(), CompareBinaryConfigs);
    }
    
    void ParseBuffer(Span<uint8_t> readBuffer)
    {
        for (auto it = m_channels.begin(); it != m_channels.end(); it++)
        {
            auto& channel = *it;
            
            Span<uint8_t> channelBuf;
            
            // end of buffer - not all channels read
            try
            {
                channelBuf = readBuffer.Slice(channel->Offset, channel->Size);
            }
            catch (...)
            {
                // todo
                throw;
            }
            
            // Allow the channel to convert itself (it knows better than we do)
            channel->Channel->PostBytes(channelBuf);
        }
    }
    
    std::vector<std::shared_ptr<OutputChannelBinaryConfiguration>> m_channels;
};
} // namespace ecu
