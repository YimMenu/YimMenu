#include "tunables_service.hpp"

#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "thread_pool.hpp"
#include "util/scripts.hpp"

namespace big
{
	tunables_service::tunables_service() :
	    m_cache_file(g_file_manager->get_project_file("./cache/tunables.bin"), 1)
	{
		m_cache_file.load();

		if (m_cache_file.up_to_date(memory::module("GTA5.exe").size()))
		{
			LOG(INFO) << "Loading tunables from cache";
			m_loading = true;

			g_thread_pool->push([this] {
				while (!g_pointers->m_gta.m_script_globals[1])
				{
					if (!m_loading)
						return;

					std::this_thread::yield();
				}

				load();
			});
		}

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

			if (m_initialized || m_loading)
				return;

			if (!m_script_started && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("tuneables_processing")) > 0)
				continue;

			if (!m_script_started)
			{
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("tuneables_processing"));

				if (SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(RAGE_JOAAT("tuneables_processing")))
				{
					std::uint64_t args[] = {6, 27, 1}; // TODO: check args

					int id = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(RAGE_JOAAT("tuneables_processing"), (Any*)args, sizeof(args) / 8, 5050);

					if (!id)
					{
						LOG(FATAL) << "Failed to start tuneables_processing. Cannot cache tunables";
						return;
					}

					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(RAGE_JOAAT("tuneables_processing"));
					m_script_started = true;

					g_script_patcher_service->add_patch({RAGE_JOAAT("tuneables_processing"), "2E ? ? 55 ? ? 38 06", 0, std::vector<uint8_t>(17, 0x0), &m_script_started}); // bool tunables registration hack
					if (auto program = gta_util::find_script_program(RAGE_JOAAT("tuneables_processing")))
						g_script_patcher_service->on_script_load(program);
				}
			}
			else
			{
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("tuneables_processing")) == 0)
				{
					if (m_tunables.size() == 0)
					{
						LOG(FATAL) << "Failed to cache tunables";
						return;
					}

					m_script_started = false;
					m_initialized    = true;
					LOG(INFO) << "Saving " << m_tunables.size() << " tunables to cache";
					g_script_patcher_service->update();
					save();
				}
			}
		}
	}

	void tunables_service::save()
	{
		auto data_size = sizeof(std::uint32_t) + sizeof(tunable_save_struct) * m_tunables.size();
		auto data      = std::make_unique<std::uint8_t[]>(data_size);
		auto data_ptr  = data.get();

		*(std::uint32_t*)data_ptr = m_tunables.size();
		data_ptr += sizeof(std::uint32_t);

		for (auto& [hash, ptr] : m_tunables)
		{
			auto save_struct    = (tunable_save_struct*)data_ptr;
			save_struct->hash   = hash;
			save_struct->offset = ((std::int64_t*)ptr) - g_pointers->m_gta.m_script_globals[1];
			data_ptr += sizeof(tunable_save_struct);
		}

		m_cache_file.set_header_version(memory::module("GTA5.exe").size());
		m_cache_file.set_data(std::move(data), data_size);
		m_cache_file.write();
	}

	void tunables_service::load()
	{
		auto data = m_cache_file.data();

		auto num_tunables = *(std::uint32_t*)data;
		data += sizeof(std::uint32_t);

		for (int i = 0; i < num_tunables; i++)
		{
			auto save_struct = (tunable_save_struct*)data;
			m_tunables.emplace(save_struct->hash, (void*)(g_pointers->m_gta.m_script_globals[1] + save_struct->offset));
			data += sizeof(tunable_save_struct);
		}

		m_initialized = true;
		m_loading     = false;
	}
}