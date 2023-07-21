#include "thread_pool.hpp"

namespace big
{
	thread_pool::thread_pool() :
	    m_accept_jobs(true)
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
		const uint32_t thread_count = std::thread::hardware_concurrency();

		LOG(VERBOSE) << "Allocating " << thread_count << " threads in thread pool.";
		this->m_thread_pool.reserve(thread_count);

		m_available_thread_count = thread_count;

		for (uint32_t i = 0; i < thread_count; i++)
			this->m_thread_pool.emplace_back(std::thread(&thread_pool::run, this));
	}

	void thread_pool::destroy()
	{
		this->m_managing_thread.join();
		{
			std::unique_lock lock(m_lock);
			this->m_accept_jobs = false;
		}
		this->m_data_condition.notify_all();

		for (auto& thread : m_thread_pool)
			thread.join();

		m_thread_pool.clear();
	}

	void thread_pool::push(std::function<void()> func, std::source_location location)
	{
		if (func)
		{
			{
				std::unique_lock lock(this->m_lock);
				this->m_job_stack.push({func, location});

				if (m_available_thread_count < m_job_stack.size())
				{
					LOG(WARNING) << "thread_pool potentially starved";
				}
			}
			this->m_data_condition.notify_all();
		}
	}

	void thread_pool::run()
	{
		for (;;)
		{
			std::unique_lock lock(this->m_lock);

			this->m_data_condition.wait(lock, [this]() {
				return !this->m_job_stack.empty() || !this->m_accept_jobs;
			});

			if (!this->m_accept_jobs)
				break;
			if (this->m_job_stack.empty())
				continue;

			thread_pool_job job = this->m_job_stack.top();
			this->m_job_stack.pop();
			lock.unlock();

			m_available_thread_count--;

			try
			{
				const auto source_file = std::filesystem::path(job.m_source_location.file_name()).filename().string();
				LOG(VERBOSE) << "Thread " << std::this_thread::get_id() << " executing " << source_file << ":"
				             << job.m_source_location.line();

				std::invoke(job.m_func);
			}
			catch (const std::exception& e)
			{
				LOG(WARNING) << "Exception thrown while executing job in thread:" << std::endl << e.what();
			}

			m_available_thread_count++;
		}

		LOG(VERBOSE) << "Thread " << std::this_thread::get_id() << " exiting...";
	}
}
