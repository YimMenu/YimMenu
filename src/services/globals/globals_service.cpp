#include "globals_service.hpp"

#include "thread_pool.hpp"

namespace big
{
	globals_service::globals_service() :
		m_globals_file(g_file_manager.get_project_file("./globals.json"))
	{ }

	globals_service::~globals_service()
	{
		m_running = false;

		save();
	}

	void globals_service::build()
	{
		m_globals.clear();

		for (auto& global : m_globals)
			global.build_cache();
	}

	bool globals_service::load()
	{
		m_globals_file;

		std::ifstream file(m_globals_file.get_path(), std::ios::binary);

		if (!file.is_open())
			return false;

		try
		{
			nlohmann::json j;
			file >> j;
			m_globals = j.get<global_vec>();

			build();
		}
		catch (const std::exception&)
		{
			LOG(WARNING) << "Failure to parse globals.json, aborting...";

			return false;
		}

		return true;
	}

	void globals_service::loop()
	{
		while (m_running)
			for (auto& global : m_globals)
				if (global.m_freeze)
					global.write();
	}

	void globals_service::save()
	{
		nlohmann::json j = m_globals;

		std::ofstream file(m_globals_file.get_path(), std::ios::binary | std::ios::out | std::ios::trunc);

		try
		{
			file << j.dump(4);

			file.close();
		}
		catch (const std::exception&)
		{
			LOG(WARNING) << "Failed to write to globals.json";
		}
	}
}