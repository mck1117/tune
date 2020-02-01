#pragma once
#include <cstddef>
#include <cstdint>

#define ASSERT(x)

template <class TBuffer = uint8_t>
class Span
{
public:
    Span() noexcept : m_buffer(nullptr), m_size(0) { }
    Span(uint8_t* buffer, size_t size) noexcept : m_buffer(buffer), m_size(size) { }
    
    // Take a slice of the buffer, starting at the specified index.
    Span Slice(size_t firstIndex)
    {
        ASSERT(m_buffer);
        ASSERT(firstIndex < m_size);

        return Span(m_buffer + firstIndex, m_size - firstIndex);
    }

    // Take a slice of the buffer, starting at the specified index, with the specified size.
    Span Slice(size_t firstIndex, size_t size)
    {
        ASSERT(m_buffer);
        ASSERT(firstIndex + size < m_size);
        
        return Span(m_buffer + firstIndex, size);
    }

    TBuffer operator[](size_t idx) const
    {
        ASSERT(m_buffer);
        ASSERT(idx < m_size);

        return m_buffer[idx];
    }

    TBuffer& operator[](size_t idx)
    {
        ASSERT(m_buffer);
        ASSERT(idx < m_size);

        return m_buffer[idx];
    }

	size_t size() const
	{
		return m_size;
	}

private:
    TBuffer* m_buffer;
    size_t m_size;

};
