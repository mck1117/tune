#include <gtest/gtest.h>

#include "channels/OutputChannel.h"

using namespace ecu;

template <class T>
Span<uint8_t> Pun(T& val)
{
	return Span(reinterpret_cast<uint8_t*>(&val), sizeof(val));
}

TEST(OutputChannel, FloatUnscaled)
{
	ScaledOutputChannel<float> ch("test", "Test Channel", { 0, 100 }, 1.0f, 0.0f);

	float testValue = 123.45;

	ch.PostBytes(Pun(testValue));

	EXPECT_EQ(ch.GetValue(), testValue);
}

TEST(OutputChannel, FloatScaled)
{
	ScaledOutputChannel<float> ch("test", "Test Channel", { 0, 100 }, 25, 0.0f);

	float testValue = 123.45;

	ch.PostBytes(Pun(testValue));

	EXPECT_EQ(ch.GetValue(), testValue / 25);
}
