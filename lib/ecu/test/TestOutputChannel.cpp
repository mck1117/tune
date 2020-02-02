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

TEST(OutputChannel, Uint16)
{
	ScaledOutputChannel<uint16_t> ch("test", "Test Channel", { 0, 100 }, 1000, 0.0f);

	uint16_t testValue = 12345;

	ch.PostBytes(Pun(testValue));

	EXPECT_FLOAT_EQ(ch.GetValue(), 12.345f);
}

TEST(OutputChannel, Int16Pos)
{
	ScaledOutputChannel<int16_t> ch("test", "Test Channel", { 0, 100 }, 1000, 0.0f);

	int16_t testValue = 12345;

	ch.PostBytes(Pun(testValue));

	EXPECT_FLOAT_EQ(ch.GetValue(), 12.345f);
}

TEST(OutputChannel, Int16Neg)
{
	ScaledOutputChannel<int16_t> ch("test", "Test Channel", { 0, 100 }, 1000, 0.0f);

	int16_t testValue = -12345;

	ch.PostBytes(Pun(testValue));

	EXPECT_FLOAT_EQ(ch.GetValue(), -12.345f);
}

