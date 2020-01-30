#include "components/Component.h"

#include <imgui.h>

class TextInput final : public Component
{
public:
	TextInput(const std::string& text, std::function<Action(const std::string&)>&& changed, size_t bufferLength = 256)
		: m_bufferLength(bufferLength)
		, m_changed(std::move(changed))
    {
		// pre-reserve buffer space so we don't allocate twice (once on the copy, once on the resize)
		m_buffer.reserve(bufferLength);
		std::copy(text.begin(), text.end(), std::back_inserter(m_buffer));
		m_buffer.resize(bufferLength);
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
		if (ImGui::InputText("test", m_buffer.data(), m_buffer.size()))
		{
			// If the input changed, convert back to a string, and dispatch
			std::string newString(m_buffer.data());

			auto changed = m_changed;
			dispatcher.Dispatch([changed, newString]() { return changed(newString); });
		}
    }

private:
	const size_t m_bufferLength;
	mutable std::vector<char> m_buffer;

    std::function<Action(const std::string&)> m_changed;
};


namespace c
{
std::unique_ptr<Component> ti(const std::string& text, std::function<Action(const std::string&)>&& changed)
{
    return std::make_unique<TextInput>(text, std::move(changed));
}
}
