
#include <ui/WindowManager.h>
#include <ui/RootState.h>
#include <ui/Dispatcher.h>
#include <ui/RootState.h>
#include <atomic>

#include <mutex>

struct WindowEntry
{
	std::function<std::unique_ptr<Component>(const RootState&)> Render;

	std::unique_ptr<Component> Current = nullptr;
};

class WindowManager final : public IWindowManager
{
public:
	void AddWindow(std::function<std::unique_ptr<Component>(const RootState&)> render) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_windows.push_back({ render, nullptr });
	}

	void Render() override
	{
		std::list<WindowEntry*> toRender;

		if (!m_isRendered.test_and_set())
		{
			printf("rendered %d\n", ++m_renderCount);

			for (auto& e : m_windows)
			{
				e.Current = e.Render(GetState());
			}
		}

		for (const auto& e : m_windows)
		{
			e.Current->Render(*m_dispatcher);
		}
	}

	RootState& GetState() override
	{
		return m_state;
	}

	void NeedsRender() override
	{
		m_isRendered.clear();
	}

private:
	std::mutex m_mutex;
	std::vector<WindowEntry> m_windows;

	RootState m_state;

	std::atomic_flag m_isRendered;
	int m_renderCount = 0;
	
	std::shared_ptr<IDispatcher> m_dispatcher = GetDispatcherInstance();
};

static WindowManager s_instance;

IWindowManager* GetWindowManager()
{
	return &s_instance;
}

RootState& GetRootState()
{
	return GetWindowManager()->GetState();
}
