#include "squad_spawner.hpp"

namespace big
{

	std::filesystem::path squad_spawner::get_file_path()
	{
		return g_file_manager->get_project_folder("SquadSpawner").get_path();
	}

	bool squad_spawner::fetch_squads()
	{
		g_squad_spawner_service.m_templates.clear();
		std::ifstream read;
		try
		{
			for (const auto& path : std::filesystem::directory_iterator(get_file_path()))
			{
				nlohmann::json j;
				if (path.path().extension() == ".json")
				{
					read.open(path.path(), std::ifstream::in);
					if (read.is_open())
					{
						read >> j;
						read.close();
					}
					//TODO ADD FROM JSON TO SQUAD STRUCT
				}
			}
			return true;
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Squad Spawner fetching files failed: " << e.what();
		}

		return false;
	}

	bool squad_spawner::save_squad(squad s)
	{
		for (auto s_ : g_squad_spawner_service.m_templates)
			if (strcmp(s_.m_name, s.m_name) == 0)
				return false;

		std::ofstream write;
		std::string savename = s.m_name;
		savename.append(".json");
		std::filesystem::path path = get_file_path() / savename;

		write.open(path, std::ofstream::out | std::ofstream::trunc);
		try
		{
			if (write.is_open())
			{
				//TODO ADD TO JSON FROM SQUAD STRUCT
				write.close();
				return true;
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Squad Spawner saving squad failed: " << e.what();
		}

		return false;
	}

	void squad_spawner::load_default_templates()
	{
		bool ped_proofs[5] = {0,0,0,0,0};
		bool ped_proofs_annoying[5] = {1, 0, 0, 1, 1};

		m_templates.push_back(squad("Swat team", "s_m_y_swat_01", "weapon_smg", "riot", 4, false, false, ped_proofs, 400, 400, 0, 75, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL));
		m_templates.push_back(squad("Secret service", "s_m_m_highsec_01", "weapon_carbinerifle", "oracle", 4, false, false, ped_proofs, 0, 200, 0, 75, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL));
		m_templates.push_back(squad("Ballas Gang", "ig_ballasog", "weapon_microsmg", "chino2", 2, false, false, ped_proofs, 0, 0, 0, 50, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::POOR));
		m_templates.push_back(squad("Grove Gang", "g_m_y_famca_01", "weapon_pistol", "chino", 2, false, false, ped_proofs, 0, 0, 0, 50, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::POOR));
		m_templates.push_back(squad("Robbers", "g_m_m_chicold_01", "weapon_smg_mk2", "baller5", 4, false, false, ped_proofs, 0, 0, 0, 65, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::AVERAGE));
		m_templates.push_back(squad("Shotgunners", "g_m_y_lost_03", "weapon_autoshotgun", "daemon", 2, false, false, ped_proofs, 0, 0, 0, 65, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::AVERAGE));
		m_templates.push_back(squad("Machete jesus", "u_m_m_jesus_01", "weapon_machete", "", 1, false, false, ped_proofs_annoying, 0, 0, 0, 10, eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel::AVERAGE));
		m_templates.push_back(squad("Annoying security guard", "mp_m_securoguard_01", "weapon_stungun_mp", "", 1, false, false, ped_proofs_annoying, 0, 0, 0, 100, eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel::PROFESSIONAL));
		m_templates.push_back(squad("Heavy attack choppers", "s_m_y_swat_01", "weapon_mg", "valkyrie", 4, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL));
		m_templates.push_back(squad("Fighter jet", "s_m_m_pilot_02", "weapon_unarmed", "lazer", 1, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::FAR_AWAY, eCombatAbilityLevel::PROFESSIONAL));
	}
}