#include "tunables_service.hpp"

#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/script_connection/script_connection_service.hpp" // for the stack size
#include "services/script_patcher/script_patcher_service.hpp"
#include "thread_pool.hpp"
#include "util/scripts.hpp"

namespace big
{
	tunables_service::tunables_service() :
	    m_cache_file(g_file_manager.get_project_file("./cache/tunables.bin"), 1)
	{
		g_tunables_service = this;
	}

	tunables_service::~tunables_service()
	{
		m_loading          = false;
		g_tunables_service = nullptr;
	}

	void tunables_service::run_script()
	{
		while (true)
		{
			script::get_current()->yield();

			m_cache_file.load();

			if (m_cache_file.up_to_date(memory::module("GTA5.exe").timestamp()))
			{
				LOG(INFO) << "Loading tunables from cache";
				m_loading = true;

				load();
			}

			if (m_initialized || m_loading)
				return;

			if (!m_script_started && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("tuneables_processing"_J) > 0)
				continue;

			if (!m_script_started)
			{
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("tuneables_processing"_J);
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("tunables_registration"_J);

				if (SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("tuneables_processing"_J) && SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("tunables_registration"_J))
				{
					m_num_tunables = gta_util::find_script_program("tunables_registration"_J)->m_global_count - TUNABLE_BASE_ADDRESS;

					uint64_t args[] = {6, 27}; // TODO: check args

					int id = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS("tuneables_processing"_J, (Any*)args, sizeof(args) / 8, DEFAULT_STACK_SIZE);

					if (!id)
					{
						LOG(FATAL) << "Failed to start tuneables_processing. Cannot cache tunables";
						return;
					}

					m_tunables_backup = std::make_unique<std::uint64_t[]>(m_num_tunables);
					memcpy(m_tunables_backup.get(), script_global(TUNABLE_BASE_ADDRESS).as<void*>(), m_num_tunables * 8);

					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("tuneables_processing"_J);
					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("tunables_registration"_J);
					m_script_started = true;
				}
			}
			else
			{
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("tuneables_processing"_J) == 0)
				{
					for (int i = 0; i < m_num_tunables; i++)
					{
						auto value = *script_global(TUNABLE_BASE_ADDRESS).at(i).as<int*>();
						if (auto it = m_junk_values.find(value); it != m_junk_values.end())
						{
							m_tunables.emplace(it->second, TUNABLE_BASE_ADDRESS + i);
						}
					}
					memcpy(script_global(TUNABLE_BASE_ADDRESS).as<void*>(), m_tunables_backup.get(), m_num_tunables * 8);

					if (m_tunables.size() == 0)
					{
						LOG(FATAL) << "Failed to cache tunables";
						return;
					}

					m_script_started = false;
					m_initialized    = true;
					LOG(INFO) << "Saving " << m_tunables.size() << " tunables to cache";
					m_tunables_backup.release();
					save();
				}
			}
		}
	}

	void tunables_service::save()
	{
		auto data_size = sizeof(uint32_t) + sizeof(tunable_save_struct) * m_tunables.size();
		auto data      = std::make_unique<uint8_t[]>(data_size);
		auto data_ptr  = data.get();

		*(uint32_t*)data_ptr = m_tunables.size();
		data_ptr += sizeof(uint32_t);

		for (auto& [hash, val] : m_tunables)
		{
			auto save_struct    = (tunable_save_struct*)data_ptr;
			save_struct->hash   = hash;
			save_struct->offset = val;
			data_ptr += sizeof(tunable_save_struct);
		}

		m_cache_file.set_header_version(memory::module("GTA5.exe").timestamp());
		m_cache_file.set_data(std::move(data), data_size);
		m_cache_file.write();
	}

	void tunables_service::load()
	{
		auto data = m_cache_file.data();

		auto num_tunables = *(uint32_t*)data;
		data += sizeof(uint32_t);

		for (int i = 0; i < num_tunables; i++)
		{
			auto save_struct = (tunable_save_struct*)data;
			m_tunables.emplace(save_struct->hash, save_struct->offset);
			data += sizeof(tunable_save_struct);
		}

		m_initialized = true;
		m_loading     = false;
	}
}
