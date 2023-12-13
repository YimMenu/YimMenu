#pragma once

namespace big
{
	// if this limit is hit you did something wrong coding wise.
	constexpr auto MAX_POOL_SIZE = 32u;

	struct thread_pool_job
	{
		std::function<void()> m_func;
		std::source_location m_source_location;
	};

	class thread_pool
	{
		std::atomic<bool> m_accept_jobs;
		std::condition_variable m_data_condition;

		std::stack<thread_pool_job> m_job_stack;
		std::mutex m_lock;
		std::vector<std::thread> m_thread_pool;

		// the amount of threads active in the pool
		std::atomic<size_t> m_allocated_thread_count;
		// the amount of threads currently on a job
		std::atomic<size_t> m_busy_threads;

	public:
		// YimMenu only has 2 blocking threads, 4 should be sufficient but the pool should automatically allocate more if needed
		thread_pool(const std::size_t preallocated_thread_count = 4);
		~thread_pool();

		void destroy();
		void push(std::function<void()> func, std::source_location location = std::source_location::current());

		std::pair<size_t, size_t> usage() const
		{ return { m_busy_threads, m_allocated_thread_count }; }

	private:
		void run();
		void rescale_thread_pool();
	};

	inline thread_pool* g_thread_pool{};
}
