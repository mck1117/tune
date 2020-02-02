#pragma once

#include <ecu/IOutputChannel.h>

#include "Span.h"

namespace ecu
{
struct OutputChannelBase : public IOutputChannel
{
	OutputChannelBase(const std::string& displayName) : m_displayName(displayName) { }

	// Update this channel using bytes read from the ECU, converting to the channel's native format
	virtual void PostBytes(Span<uint8_t> buffer) = 0;

	const std::string& GetDisplayName() const override
	{
		return m_displayName;
	}

private:
	const std::string m_displayName;
};

template <class TValue>
class ScalarOutputChannel : public OutputChannelBase
{
public:
	ScalarOutputChannel(const std::string& id, const std::string& displayName, ChannelBounds<TValue> bounds)
		: OutputChannelBase(displayName)
		, Id(id)
		, Bounds(bounds)
	{
	}

	// OutputChannelBase implementation
	float GetValueAsFloat() const override
	{
		return GetValue();
	}

	ChannelBounds<float> GetBoundsAsFloat() const override
	{
		return ChannelBounds<float>(Bounds.Min, Bounds.Max);
	}

	virtual void SetValue(TValue newValue)
	{
		m_value.store(newValue);
	}

	const TValue GetValue() const
	{
		return m_value.load();
	}

	const std::string Id;
	const ChannelBounds<TValue> Bounds;

private:
	std::atomic<TValue> m_value = 0;
};

template <class TStorage>
class ScaledOutputChannel final : public ScalarOutputChannel<float>
{
public:
	ScaledOutputChannel(const std::string& id, const std::string& displayName, ChannelBounds<float> bounds, float scale = 1.0f, float add = 1.0f)
		: ScalarOutputChannel(id, displayName, bounds)
		, m_scale(scale)
		, m_add(add)
	{
	}

	void PostBytes(Span<uint8_t> b) override
	{
		if constexpr (std::is_same_v<TStorage, float>)
		{
			uint32_t raw =
				(b[0] << 0) |
				(b[1] << 8) |
				(b[2] << 16) |
				(b[3] << 24);

			SetValueUnscaled(*(float*)(&raw));
		}
		else if constexpr (std::is_same_v<TStorage, uint16_t>)
		{
			SetValueUnscaled(b[1] << 8 | b[0]);
		}
		else if constexpr (std::is_same_v < TStorage, int16_t>)
		{
			int16_t val = b[1] << 8 | b[0];
			SetValueUnscaled(val);
		}
	}

private:
	void SetValueUnscaled(float unscaled)
	{
		SetValue(unscaled / m_scale + m_add);
	}
	
	const float m_scale;
	const float m_add;
};

using FloatOutputChannel = ScaledOutputChannel<float>;

}