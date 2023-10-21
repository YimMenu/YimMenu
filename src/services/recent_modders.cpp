#pragma once

using json = nlohmann::json;

namespace recent_modders_nm
{
	struct recent_modder
	{
		std::string name;
		uint64_t rockstar_id;
		bool block_join = true;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(recent_modder, name, rockstar_id);

	inline std::map<uint64_t, recent_modder> recent_modders_list;

	inline std::filesystem::path getSavedFilePath()
	{
		return big::g_file_manager.get_project_file("blocked_modders.json").get_path();
	}
	inline void load_blocked_list()
	{
		try
		{
			if (auto filePath = getSavedFilePath(); std::filesystem::exists(filePath))
			{
				std::ifstream f(filePath);

				if (f.is_open())
				{
					recent_modders_list = json::parse(f);
					f.close();
				}
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << e.what();
		}
	}

	inline void save_blocked_list()
	{
		std::map<uint64_t, recent_modder> filtered_map;
		for (const auto& entry : recent_modders_list)
			if (entry.second.block_join)
				filtered_map[entry.first] = entry.second;

		try
		{
			json j = filtered_map;
			if (std::ofstream o(getSavedFilePath()); o.is_open())
			{
				o << std::setw(4) << j << std::endl;
				o.close();
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << e.what();
		}
	}
}