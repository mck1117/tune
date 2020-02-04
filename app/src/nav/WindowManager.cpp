
#include "WindowManager.h"
#include "Window.h"
#include "state/RootState.h"
#include "dispatcher/Dispatcher.h"
#include <atomic>

#include <mutex>

class WindowManager final : public IWindowManager
{
public:
	void AddWindow(const std::shared_ptr<Window>& window) override
	{
		m_windows.push_back(window);
	}

	void Render() override
	{
        // If we need to rerender windows, do so
		if (!m_isRendered.test_and_set())
		{
			printf("rendered %d\n", ++m_renderCount);

            auto it = m_windows.begin();
            
            while (it != m_windows.end())
            {
                auto window = *it;
                
                window->Build();
                
                // Remove from the list if deleted
                if (window->IsDeleted())
                {
                    it = m_windows.erase(it);
                }
                else
                {
                    it++;
                }
            }
		}

        // Now draw all windows
		for (const auto& e : m_windows)
		{
			e->Render(*m_dispatcher);
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
	std::vector<std::shared_ptr<Window>> m_windows;

	RootState m_state;

	std::atomic_flag m_isRendered{};
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
