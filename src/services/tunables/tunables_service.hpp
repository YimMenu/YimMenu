#pragma once
#include "fiber_pool.hpp"
#include "script.hpp"
#include "services/gta_data/cache_file.hpp"
#include "script_global.hpp"

namespace big
{
	constexpr int TUNABLE_BASE_ADDRESS = 0x40001; // This never changes

#pragma pack(push, 1)
	struct tunable_save_struct
	{
		rage::joaat_t hash;
		uint32_t offset;
	};
#pragma pack(pop)

	class tunables_service
	{
	public:
		tunables_service();
		~tunables_service();
		void run_script();

		inline bool caching_tunables()
		{
			return m_script_started;
		}

		inline bool initialized()
		{
			return m_initialized;
		}

		template<typename T>
		inline std::enable_if_t<std::is_pointer_v<T>, T> get_tunable(rage::joaat_t hash)
		{
			if (auto it = m_tunables.find(hash); it != m_tunables.end())
				return reinterpret_cast<T>(script_global(it->second).as<void*>());

			return nullptr;
		}

		// wrapper around get_tunable(), may not set the tunable immediately if the service isn't initialized yet
		template<typename T>
		inline void set_tunable(rage::joaat_t hash, T value)
		{
			if (initialized())
			{
				if (auto tunable = get_tunable<T*>(hash))
				{
					*tunable = value;
				}
				else
				{
					LOG(WARNING) << "Tunable 0x" << hash << " not found.";
				}
			}
			else
			{
				g_fiber_pool->queue_job([this, hash, value] {
					while (!initialized())
						script::get_current()->yield();

					if (auto tunable = get_tunable<T*>(hash))
					{
						*tunable = value;
					}
				});
			}
		}

		inline int get_tunable_offset(rage::joaat_t hash)
		{
			if (auto it = m_tunables.find(hash); it != m_tunables.end())
			{
				auto offset = it->second;

				if (offset > TUNABLE_BASE_ADDRESS)
					return (offset - TUNABLE_BASE_ADDRESS);

				return (TUNABLE_BASE_ADDRESS - offset);
			}

			return 0;
		}

		int m_current_junk_val = 0x1000000;
		std::unordered_map<int, rage::joaat_t> m_junk_values{};

	private:
		bool m_initialized    = false;
		bool m_loading        = false;
		bool m_script_started = false;

		cache_file m_cache_file;

		std::unordered_map<rage::joaat_t, int> m_tunables{};
		std::unique_ptr<uint64_t[]> m_tunables_backup; 
		int m_num_tunables;

		void save();
		void load();
	};

	inline tunables_service* g_tunables_service;
}