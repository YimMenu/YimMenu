#include "batch.hpp"

#include <future>//std::async



namespace memory
{


	/*template<size_t N>
	bool memory::batch<N>::run(range region) const
	{
		for (auto& entry : m_entries)
		{
			g_futures.emplace_back(std::async(&scan_pattern_and_execute_callback, region, entry));
		}

		bool found_all_patterns = true;
		for (auto& future : g_futures)
		{
			future.wait();

			if (!future.get())
				found_all_patterns = false;
		}

		g_futures.clear();

		return found_all_patterns;
	}*/
}
