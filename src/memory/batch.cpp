#include "../common.hpp"
#include "../logger.hpp"
#include "batch.hpp"
#include "range.hpp"

#include <future> //std::async

#define ASYNC_PATTERN_SCANNER 1
#define LOG_SCAN_TIME 1


static std::mutex s_entry_mutex;
static std::vector<std::future<void>> m_futures;

namespace memory
{
	void batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void run_function_detour_route(range region, memory::batch::entry entry)
	{
		bool all_found = true;

		if (auto result = region.scan(entry.m_pattern))
		{
			if (entry.m_callback)
			{
				std::lock_guard<std::mutex> lock(s_entry_mutex); 

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
			throw std::runtime_error("Failed to find some patterns.");
		}
	}

	void batch::run(range region)
	{

#if LOG_SCAN_TIME
		auto start = std::chrono::high_resolution_clock::now();
#endif

		for (auto& entry : m_entries)
		{
#if ASYNC_PATTERN_SCANNER
			m_futures.push_back(std::async(std::launch::async, run_function_detour_route, region, entry)); //Save the return(because some guy said so)
#else
			run_function_detour_route(region, entry);
#endif
		}
#if LOG_SCAN_TIME
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		LOG(INFO) << "Finished pattern scanning in " << duration.count() << " microseconds.";
#endif
		
		m_entries.clear();
		m_futures.clear();
		
	}
}
