#pragma once
#include "fiber_pool.hpp"
#include "script.hpp"
#include "services/gta_data/cache_file.hpp"

namespace big
{
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

		inline void register_tunable(rage::joaat_t hash, void* pointer)
		{
			m_tunables.emplace(hash, pointer);
		}

		template<typename T>
		inline std::enable_if_t<std::is_pointer_v<T>, T> get_tunable(rage::joaat_t hash)
		{
			if (auto it = m_tunables.find(hash); it != m_tunables.end())
				return reinterpret_cast<T>(it->second);

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
					LOG(INFO) << "Imm set";
				}
				else
				{
					LOG(INFO) << "Not found";
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

						LOG(INFO) << "Delay set";
					}
				});
			}
		}

	private:
		bool m_initialized    = false;
		bool m_loading        = false;
		bool m_script_started = false;

		cache_file m_cache_file;

		std::unordered_map<rage::joaat_t, void*> m_tunables{};

		void save();
		void load();
	};

	inline tunables_service* g_tunables_service;
}