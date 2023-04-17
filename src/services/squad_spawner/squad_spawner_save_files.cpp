#include "squad_spawner.hpp"

namespace big
{

	std::filesystem::path squad_spawner::get_file_path()
	{
		return g_file_manager->get_project_folder("squad_spawner").get_path();
	}

	nlohmann::json squad_spawner::to_json(squad s)
	{
		nlohmann::json j;

		j["name"]                    = s.m_name;
		j["description"]             = s.m_description;
		j["pedmodel"]                = s.m_ped_model;
		j["vehmodel"]                = s.m_vehicle_model;
		j["weapmodel"]               = s.m_weapon_model;
		j["pedinvincibility"]        = s.m_ped_invincibility;
		j["vehinvincibility"]        = s.m_veh_invincibility;
		j["pedproofs"]["headshot"]   = s.m_ped_proofs[0];
		j["pedproofs"]["bullet"]     = s.m_ped_proofs[1];
		j["pedproofs"]["flame"]      = s.m_ped_proofs[2];
		j["pedproofs"]["melee"]      = s.m_ped_proofs[3];
		j["pedproofs"]["explosion"]  = s.m_ped_proofs[4];
		j["pedhealth"]               = s.m_ped_health;
		j["pedarmor"]                = s.m_ped_armor;
		j["pedacurracy"]             = s.m_ped_accuracy;
		j["spawndistance"]           = s.m_spawn_distance;
		j["squadsize"]               = s.m_squad_size;
		j["spawndistancemode"]       = s.m_spawn_distance_mode;
		j["combatabilitylevel"]      = s.m_combat_ability_level;
		j["stayinveh"]               = s.m_stay_in_veh;
		j["spawnbehindsamevelocity"] = s.m_spawn_behind_same_velocity;

		return j;
	}

	squad squad_spawner::from_json(nlohmann::json j)
	{
		squad new_squad;
		std::string_view name_sv       = j["name"];
		std::string_view desc_sv       = j["description"];
		std::string_view ped_model_sv  = j["pedmodel"];
		std::string_view veh_model_sv  = j["vehmodel"];
		std::string_view weap_model_sv = j["weapmodel"];

		strcpy(new_squad.m_name, name_sv.data());
		strcpy(new_squad.m_description, desc_sv.data());
		strcpy(new_squad.m_ped_model, ped_model_sv.data());
		strcpy(new_squad.m_vehicle_model, veh_model_sv.data());
		strcpy(new_squad.m_weapon_model, weap_model_sv.data());

		new_squad.m_ped_invincibility = j["pedinvincibility"];
		new_squad.m_veh_invincibility = j["vehinvincibility"];
		new_squad.m_ped_proofs[0]     = j["pedproofs"]["headshot"];
		new_squad.m_ped_proofs[1]     = j["pedproofs"]["bullet"];
		new_squad.m_ped_proofs[2]     = j["pedproofs"]["flame"];
		new_squad.m_ped_proofs[3]     = j["pedproofs"]["melee"];
		new_squad.m_ped_proofs[4]     = j["pedproofs"]["explosion"];
		new_squad.m_ped_health        = j["pedhealth"];
		new_squad.m_ped_armor         = j["pedarmor"];
		new_squad.m_ped_accuracy      = j["pedacurracy"];
		new_squad.m_spawn_distance    = j["spawndistance"];
		new_squad.m_squad_size        = j["squadsize"];

		new_squad.m_spawn_distance_mode  = j["spawndistancemode"];
		new_squad.m_combat_ability_level = j["combatabilitylevel"];

		new_squad.m_stay_in_veh                = j["stayinveh"];
		new_squad.m_spawn_behind_same_velocity = j["spawnbehindsamevelocity"];

		return new_squad;
	}

	bool squad_spawner::fetch_squads()
	{
		g_squad_spawner_service.m_templates.clear();
		bool success = false;
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
					g_squad_spawner_service.m_templates.push_back(g_squad_spawner_service.from_json(j));
				}
			}
			success = true;
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Squad Spawner fetching files failed: " << e.what();
		}

		g_squad_spawner_service.load_default_templates();
		return success;
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
				write << std::setw(4) << squad_spawner::to_json(s) << std::endl;
				write.close();
				g_notification_service->push("Squad spawner", std::string("Succesfully saved ").append(s.m_name));
				fetch_squads();
				return true;
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Squad Spawner saving squad failed: " << e.what();
		}

		return false;
	}

	bool squad_spawner::delete_squad(squad s)
	{
		std::string savename = s.m_name;
		savename.append(".json");
		std::filesystem::path path = get_file_path() / savename;
		std::filesystem::remove(path);
		return fetch_squads();
	}

	void squad_spawner::load_default_templates()
	{
		bool ped_proofs[5]          = {0, 0, 0, 0, 0};
		bool ped_proofs_annoying[5] = {1, 0, 0, 1, 1};

		m_templates.push_back(squad("Swat team", "s_m_y_swat_01", "WEAPON_SMG", "riot", 4, false, false, ped_proofs, 400, 400, 0, 75, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL, false, false, "An elite team of swat operatives that will quickly swarm the target"));
		m_templates.push_back(squad("Secret service", "s_m_m_highsec_01", "WEAPON_CARBINERIFLE", "oracle", 4, false, false, ped_proofs, 0, 200, 0, 75, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL, false, false, "MIB"));
		m_templates.push_back(squad("Ballas Gang", "ig_ballasog", "WEAPON_MICROSMG", "chino2", 2, false, false, ped_proofs, 0, 0, 0, 50, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::POOR, true, false, "A classic driveby from the local Ballas gang"));
		m_templates.push_back(squad("Grove Gang", "g_m_y_famca_01", "WEAPON_PISTOL", "chino", 2, false, false, ped_proofs, 0, 0, 0, 50, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::POOR, true, false, "A classic driveby from the local Grove gang"));
		m_templates.push_back(squad("Robbers", "g_m_m_chicold_01", "WEAPON_SMG_MK2", "baller5", 4, false, false, ped_proofs, 0, 0, 0, 65, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::AVERAGE, false, false, "Mysterious mercenaries that hide behind snow masks"));
		m_templates.push_back(squad("Shotgunners", "g_m_y_lost_03", "WEAPON_AUTOSHOTGUN", "daemon", 2, false, false, ped_proofs, 0, 0, 0, 65, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::AVERAGE, false, false, "A duo biker gang that utilize sawn off shotguns on their Harley's"));
		m_templates.push_back(squad("Machete jesus", "u_m_m_jesus_01", "WEAPON_MACHETE", "", 1, false, false, ped_proofs_annoying, 0, 0, 0, 10, eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel::AVERAGE, false, false, "Christ has had enough of the sins"));
		m_templates.push_back(squad("Annoying security guard", "mp_m_securoguard_01", "WEAPON_STUNGUN_MP", "", 1, false, false, ped_proofs_annoying, 0, 0, 0, 100, eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel::PROFESSIONAL, false, false, "The mall security guard with superiority issues"));
		m_templates.push_back(squad("Heavy attack choppers", "s_m_y_swat_01", "WEAPON_MG", "valkyrie", 4, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::MODERATELY_DISTANCED, eCombatAbilityLevel::PROFESSIONAL, false, false, "Very deadly attack chopper eqquiped with a cannon"));
		m_templates.push_back(squad("Fighter jet", "s_m_m_pilot_02", "WEAPON_UNARMED", "lazer", 1, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::FAR_AWAY, eCombatAbilityLevel::PROFESSIONAL, false, false, "Tedious yet precise form of attack with a Fighter jet"));
		m_templates.push_back(squad("Mobile squad", "s_m_m_highsec_01", "WEAPON_MICROSMG", "komoda", 4, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::FAR_AWAY, eCombatAbilityLevel::PROFESSIONAL, true, true, "This squad makes use of 'Vehicle catchup'"));
		m_templates.push_back(squad("Altruists", "a_m_m_acult_01", "WEAPON_KNIFE", "", 8, false, false, ped_proofs, 0, 0, 0, 100, eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel::PROFESSIONAL, false, false, "Cannibals fromt the alrtuist cult"));
	}
}