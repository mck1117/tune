#include <ui/Component.h>

#include <imgui.h>

class TextInput final : public Component
{
public:
	TextInput(std::function<Action(const std::string&)>&& changed, size_t bufferLength = 256)
		: m_bufferLength(bufferLength)
		, m_changed(std::move(changed))
    {
		m_buffer.resize(bufferLength);
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
		if (ImGui::InputText("test", m_buffer.data(), m_buffer.size()))
		{
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
std::unique_ptr<Component> ti(std::function<Action(const std::string&)>&& changed)
{
    return std::make_unique<TextInput>(std::move(changed));
}
}
