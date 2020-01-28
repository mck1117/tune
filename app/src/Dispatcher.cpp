#include <ui/Dispatcher.h>

#include <memory>
#include <mutex>
#include <list>
#include <thread>

class ThreadDispatcher final : public IDispatcher
{
public:
    ThreadDispatcher()
    {
        m_thread = std::thread([this]() { Run(); });
    }

	~ThreadDispatcher()
	{
		Shutdown();
	}

	void Shutdown()
	{
		if (m_thread.joinable())
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_exiting = true;
			}

			m_actionRequired.notify_one();
			m_thread.join();
		}
	}
    
    void Dispatch(Callback&& func) override
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            m_queue.push_back(std::move(func));
        }
        
        m_actionRequired.notify_one();
    }
                     
private:
    void Run()
    {
        while(true)
        {
            std::list<Callback> tempQueue;
            
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                
                // Wait for signal
                m_actionRequired.wait(lock);
                
				if (m_exiting)
				{
					return;
				}

                tempQueue = std::move(m_queue);
            }
            
            while(!tempQueue.empty())
            {
                auto work = std::move(tempQueue.front());
                tempQueue.pop_front();
                
                Action a = work();
                a(*this, GetRootState());
            }
        }
    }
    
    std::thread m_thread;
    
    std::mutex m_mutex;
    std::condition_variable m_actionRequired;
    
    std::list<Callback> m_queue;

	bool m_exiting = false;
};

std::shared_ptr<IDispatcher> GetDispatcherInstance()
{
    return std::make_shared<ThreadDispatcher>();
}
