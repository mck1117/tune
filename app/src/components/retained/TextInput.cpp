#include <ui/Component.h>

#include <imgui.h>


class TextInput final : public Component
{
public:
    TextInput(std::function<Action(const std::string&)>&& changed)
        : m_changed(std::move(changed))
    {
    }

protected:
    void Render(IDispatcher& dispatcher) const override
    {
		// todo: this is probably very wrong

		std::vector<char> str(m_string.begin(), m_string.end());
		str.push_back(0);
		str.reserve(128);

		ImGui::InputText("test", str.data(), 128);

		std::string newString = std::string(str.data());

		if (newString != m_string)
		{
			m_string = newString;

			auto changed = m_changed;
			dispatcher.Dispatch([changed, newString]() { return changed(newString); });
		}
    }

private:
    mutable std::string m_string;
    std::function<Action(const std::string&)> m_changed;
};


namespace c
{
std::unique_ptr<Component> ti(std::function<Action(const std::string&)>&& changed)
{
    return std::make_unique<TextInput>(std::move(changed));
}
}
