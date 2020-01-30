#pragma once

#include <atomic>
#include <string>

namespace ecu
{

template <class TValue>
struct ChannelBounds
{
    ChannelBounds(TValue min, TValue max) : Min(min), Max(max) { }

    const TValue Min;
    const TValue Max;
};

struct IOutputChannel
{  
    virtual ~IOutputChannel() = default;

	virtual float GetValueAsFloat() const = 0;
	virtual ChannelBounds<float> GetBoundsAsFloat() const = 0;

    // todo: remove me!
	virtual void SetValue(float) = 0;

	virtual const std::string& GetDisplayName() const = 0;
};
}
