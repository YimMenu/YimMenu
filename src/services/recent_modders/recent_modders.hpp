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

	extern std::map<uint64_t, recent_modder> recent_modders_list;

	inline std::filesystem::path getSavedFilePath()
	{
		return big::g_file_manager.get_project_file("blocked_modders.json").get_path();
	}
	
	void load_blocked_list();
	void save_blocked_list();

	inline void add_player(recent_modder modder)
	{
		recent_modders_nm::recent_modders_list[modder.rockstar_id] = modder;
		save_blocked_list();
	}
}