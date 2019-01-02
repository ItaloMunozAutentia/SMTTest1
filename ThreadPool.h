//============================================================================
// Name        : ThreadPool.h
// Author      :
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of ThreadPool class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

/* CLASS DECLARATION *********************************************************/

class ThreadPool
{
public:
	/**
	 * @brief Creates a pool of <threads> threads
	 *
	 */
	explicit ThreadPool(size_t threads);

	/**
	 * @brief Adds a task to the queue
	 *
	 */
	template<class F, class... Args>
	auto Enqueue(F&& f, Args&&... args)
		-> std::future<typename std::result_of<F(Args...)>::type>;

	/**
	 * @brief TODO
	 *
	 */
	~ThreadPool();

private:
	std::vector<std::thread>          m_workers;
	std::queue<std::function<void()>> m_tasks;
	// sync stuff
	std::mutex              m_queueMutex;
	std::condition_variable m_condition;
	bool                    m_stop;
};

/* CLASS IMPLEMENTATION ******************************************************/

ThreadPool::ThreadPool(size_t threads)
	: m_stop(false)
{
	for(size_t i = 0;i<threads;++i)
	{
		m_workers.emplace_back
		(
			[this]
			{
				while (true)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(this->m_queueMutex);
						this->m_condition.wait
						(
							lock,
							[this]
							{
								return this->m_stop || !this->m_tasks.empty();
							}
						);
						if(this->m_stop && this->m_tasks.empty())
						{
							return;
						}

						task = std::move(this->m_tasks.front());
						this->m_tasks.pop();
					}
					task();
				}
			}
		);
	}
}

template<class F, class... Args>
auto ThreadPool::Enqueue(F&& f, Args&&... args)
	-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;
	auto task = std::make_shared<std::packaged_task<return_type()>>
		(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(m_queueMutex);
		// Attempting to enqueue on stopped pool?
		if(m_stop)
		{
			throw std::runtime_error("Attempting to enqueue on stopped pool");
		}

		m_tasks.emplace([task](){ (*task)(); });
	}
	m_condition.notify_one();
	return res;
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(m_queueMutex);
		m_stop = true;
	}
	m_condition.notify_all();
	for(std::thread &worker: m_workers)
	{
		worker.join();
	}
}
