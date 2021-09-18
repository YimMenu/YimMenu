#include "thread_pool.hpp"

namespace big
{
	thread_pool::thread_pool() : m_accept_jobs(true), m_data_condition(), m_job_stack(), m_lock()
	{
		this->m_managing_thread = std::thread(&thread_pool::create, this);

		g_thread_pool = this;
	}

	thread_pool::~thread_pool()
	{
		g_thread_pool = nullptr;
	}

	void thread_pool::create()
	{
		int thread_count = std::thread::hardware_concurrency();

		LOG(INFO) << "Allocating " << thread_count << " threads in thread pool.";
		this->m_thread_pool.reserve(thread_count);

		for (int i = 0; i < thread_count; i++)
			this->m_thread_pool.push_back(std::thread(&thread_pool::run, this));
	}

	void thread_pool::destroy()
	{
		this->m_managing_thread.join();

		this->done();

		for (int i = 0; i < this->m_thread_pool.size(); i++)
			this->m_thread_pool.at(i).join();
	}

	void thread_pool::done()
	{
		std::unique_lock<std::mutex> lock(this->m_lock);
		this->m_accept_jobs = false;

		lock.unlock();
		this->m_data_condition.notify_all();
	}

	void thread_pool::push(std::function<void()> func)
	{
		if (func)
		{
			std::unique_lock<std::mutex> lock(this->m_lock);
			this->m_job_stack.push(std::move(func));

			lock.unlock();
			this->m_data_condition.notify_all();
		}
	}

	void thread_pool::run()
	{
		for (;;)
		{
			std::unique_lock<std::mutex> lock(this->m_lock);

			this->m_data_condition.wait(lock, [this]()
			{
				return !this->m_job_stack.empty() || !this->m_accept_jobs;
			});

			if (!this->m_accept_jobs) return;
			if (this->m_job_stack.empty()) continue;

			auto job = std::move(this->m_job_stack.top());
			this->m_job_stack.pop();
			lock.unlock();

			try
			{
				std::invoke(std::move(job));
			}
			catch (const std::exception& e)
			{
				LOG(WARNING) << "Exception thrown while executing job in thread:" << std::endl << e.what();
			}
		}

		LOG(INFO) << "Thread " << std::this_thread::get_id() << " exiting...";
	}
}