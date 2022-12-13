#pragma once

#include "logger.hpp"

namespace big
{
	using namespace std::chrono;
	class benchmark
	{
	public:
		explicit benchmark(std::string name = "") : 
			m_start(high_resolution_clock::now()), m_name(name) {}

		void get_runtime()
		{
			auto now = high_resolution_clock::now();
			auto milliseconds_elapsed = duration_cast<milliseconds>(now - m_start);
			auto microseconds_elapsed = duration_cast<microseconds>(now - m_start);
			LOG(INFO) << m_name << " finished with a resulting time of: " << milliseconds_elapsed.count() << "ms " << microseconds_elapsed.count() % 1000 << "us";
		}

		void reset()
		{
			m_start = high_resolution_clock::now();
		}
	private:
		high_resolution_clock::time_point m_start;
		std::string m_name;
	};
}
