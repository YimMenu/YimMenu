#include "globals_service.hpp"

#include "thread_pool.hpp"

namespace big
{
	globals_service::globals_service()
	{
		g_globals_service = this;
	}

	globals_service::~globals_service()
	{
		g_globals_service = nullptr;

		m_running = false;

		this->save();
	}

	void globals_service::build(nlohmann::json& data)
	{
		m_globals.clear();

		for (auto& offset : data)
			m_globals.push_back(global(offset));

		for (auto& global : m_globals)
			global.build_cache();
	}

	bool globals_service::load()
	{
		std::string path = std::getenv("appdata");
		path += this->file_location;

		std::ifstream file(path);

		if (!file.is_open())
			return false;

		try
		{
			nlohmann::json j;
			j << file;

			this->build(j);
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
		nlohmann::json j = nlohmann::json::array();
		for (auto& global : m_globals)
			j.push_back(global.to_json());

		std::string path = std::getenv("appdata");
		path += this->file_location;
		std::ofstream file(path, std::ios::out | std::ios::trunc);

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