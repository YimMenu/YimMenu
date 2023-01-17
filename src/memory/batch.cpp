#include "../common.hpp"
#include "../logger.hpp"
#include "batch.hpp"
#include "range.hpp"
#include "fiber_pool.hpp"
#include "backend/looped_command.hpp"

#include <future> //std::async

static std::mutex s_entry_mutex;
static std::vector<std::future<void>> m_futures;

namespace memory
{
	void batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void scan_pattern_and_execute_callback(range region, memory::batch::entry entry)
	{
		bool all_found = true;

		if (auto result = region.scan(entry.m_pattern))
		{
			if (entry.m_callback)
			{
				std::lock_guard<std::mutex> lock(s_entry_mutex); // Acquire a lock on the mutex to synchronize access.

				std::invoke(std::move(entry.m_callback), result);
				std::stringstream file_out{}; //I hate this, but not logging it except on fail really helps on speed.
				file_out << "Found '" << entry.m_name << "' GTA5.exe+" << HEX_TO_UPPER(result.as<DWORD64>() - region.begin().as<DWORD64>());
				big::g_log->file_out(file_out);
				file_out.clear();
			}		
			else
			{
				all_found = false;
				LOG(WARNING) << "Failed to find '" << entry.m_name << "'.";
			}
		}
		else
		{
			all_found = false;
			LOG(WARNING) << "Failed to find '" << entry.m_name << "'.";
		}

		if (!all_found)
		{
			LOG(WARNING) << "Failed to find some patterns.";
			//Unload here.
		}
	}

	void batch::run(range region)
	{
		for (auto& entry : m_entries)
		{
			m_futures.emplace_back(std::async(std::launch::async, scan_pattern_and_execute_callback, region, entry)); //Save the return.
		}

		std::for_each(m_futures.begin(), m_futures.end(),
		std::mem_fn(&std::future<void>::wait));

		m_entries.clear();
		m_futures.clear();
	}
}
