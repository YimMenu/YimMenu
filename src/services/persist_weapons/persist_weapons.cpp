#include "persist_weapons.hpp"

#include "gta/weapons.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	static weaponloadout_json persist_weapon_loadout;

	void persist_weapons::save_weapons(std::string loadout_name)
	{
		Player player  = self::id;
		Ped player_ped = self::ped;
		weaponloadout_json weapon_json{};
		for (const auto& [name, weapon] : g_gta_data_service.weapons())
		{
			Hash weapon_hash = weapon.m_hash;
			if (weapon_hash != WEAPON_UNARMED && WEAPON::HAS_PED_GOT_WEAPON(player_ped, weapon_hash, FALSE))
			{
				weaponloadout_weapon_json weapon_loadout;
				weapon_loadout.weapon = weapon_hash;
				weapon_loadout.group  = rage::joaat("GROUP_" + weapon.m_weapon_type);
				weapon_loadout.tint   = WEAPON::GET_PED_WEAPON_TINT_INDEX(player_ped, weapon_hash);
				for (auto component : weapon.m_attachments)
				{
					Hash component_hash = rage::joaat(component);
					if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(player_ped, weapon_hash, component_hash))
						weapon_loadout.component_array.push_back(component_hash);
				}
				weapon_json.weapons.push_back(weapon_loadout);
			}
		}
		if (WEAPON::HAS_PED_GOT_WEAPON(player_ped, GADGET_PARACHUTE, FALSE))
		{
			weapon_json.parachutes = 1;
			int parachute_tint, parachute_pack_tint, reserve_pack_tint, smoke_trail[3]{};
			bool hasReserve = PLAYER::GET_PLAYER_HAS_RESERVE_PARACHUTE(player);
			PLAYER::GET_PLAYER_PARACHUTE_TINT_INDEX(player, &parachute_tint);
			PLAYER::GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(player, &parachute_pack_tint);
			weapon_json.parachute_tint      = parachute_tint;
			weapon_json.parachute_pack_tint = parachute_pack_tint;
			if (hasReserve == true)
			{
				weapon_json.parachutes = 2;
				PLAYER::GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(player, &reserve_pack_tint);
				weapon_json.reserve_pack_tint = reserve_pack_tint;
			}
			PLAYER::GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(player,
			    &weapon_json.smoke_trail[0],
			    &weapon_json.smoke_trail[1],
			    &weapon_json.smoke_trail[2]);
		}

		nlohmann::json json_output_file = weapon_json;
		const auto file                 = get_weapon_config_folder().get_file(loadout_name + ".json");
		std::ofstream file_stream(file.get_path(), std::ios::out | std::ios::trunc);
		file_stream << json_output_file.dump(4);
		file_stream.close();
	}

	void persist_weapons::set_weapon_loadout(std::string loadout_name)
	{
		if (loadout_name.empty())
			return;

		g.persist_weapons.weapon_loadout_file = loadout_name;
		persist_weapon_loadout                = get_loadout(loadout_name);
	}

	void persist_weapons::check_player_has_weapons()
	{
		if (!g.persist_weapons.enabled)
		{
			return;
		}

		if (persist_weapon_loadout.weapons.empty())
		{
			if (g.persist_weapons.weapon_loadout_file.empty())
			{
				return;
			}
			persist_weapon_loadout = get_loadout(g.persist_weapons.weapon_loadout_file);
		}

		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr || g_local_player->m_player_info->m_game_state == eGameState::InMPCutscene || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() || DLC::GET_IS_LOADING_SCREEN_ACTIVE()) [[unlikely]]
		{
			return;
		}

		give_Loadout(persist_weapon_loadout);
	}

	void persist_weapons::give_player_loadout(std::string loadout_name)
	{
		give_Loadout(get_loadout(loadout_name));
	}

	weaponloadout_json persist_weapons::get_loadout(std::string loadout_name)
	{
		auto file = get_weapon_config_folder().get_file(loadout_name);

		if (file.exists())
		{
			std::ifstream file_stream(file.get_path());
			try
			{
				nlohmann::json json_input_file;

				file_stream >> json_input_file;
				file_stream.close();

				weaponloadout_json loadout = json_input_file;
				return loadout;
			}
			catch (std::exception& e)
			{
				g_notification_service.push_warning("Persist Weapons", "Failed to load JSON file from disk.");
				LOG(WARNING) << "Persist Weapons failed to load JSON file: " << g.persist_weapons.weapon_loadout_file << " because " << e.what();
			}
		}
		else
		{
			g.persist_weapons.weapon_loadout_file.clear();
			LOG(WARNING) << "persist_weapons cannot open file" << g.persist_weapons.weapon_loadout_file;
		}
		return {};
	}

	big::folder persist_weapons::get_weapon_config_folder()
	{
		const auto folder = g_file_manager.get_project_folder("./weapon_loadouts");

		return folder;
	}

	std::vector<std::string> persist_weapons::list_weapon_loadouts()
	{
		std::vector<std::string> file_paths;

		const auto file_path = get_weapon_config_folder();
		for (const auto& directory_entry : std::filesystem::directory_iterator(file_path.get_path()))
			if (directory_entry.path().extension() == ".json")
				file_paths.push_back(directory_entry.path().filename().generic_string());

		return file_paths;
	}

	void persist_weapons::give_Loadout(const weaponloadout_json& loadout)
	{
		Player player  = self::id;
		Ped player_ped = self::ped;
		if (PED::IS_PED_DEAD_OR_DYING(player_ped, true)) [[unlikely]]
			return;

		for (auto weapon : loadout.weapons)
		{
			Hash weapon_hash = weapon.weapon;
			bool is_gun      = (weapon.group != GROUP_MELEE);
			if (WEAPON::HAS_PED_GOT_WEAPON(player_ped, weapon_hash, FALSE) == false
			    || (is_gun && (WEAPON::GET_PED_WEAPON_TINT_INDEX(player_ped, weapon_hash) != weapon.tint || (WEAPON::GET_AMMO_IN_PED_WEAPON(player_ped, weapon_hash) == 0))))
			{
				int maxAmmo;
				if (WEAPON::GET_MAX_AMMO(player_ped, weapon_hash, &maxAmmo) == FALSE)
					maxAmmo = 9999;
				WEAPON::GIVE_WEAPON_TO_PED(player_ped, weapon_hash, maxAmmo, FALSE, FALSE);
				if (weapon.group != GROUP_MELEE)
				{
					WEAPON::SET_PED_WEAPON_TINT_INDEX(player_ped, weapon_hash, weapon.tint);
					for (auto component : g_gta_data_service.weapon_by_hash(weapon_hash).m_attachments)
						WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(player_ped, weapon_hash, rage::joaat(component));
					for (auto component : weapon.component_array)
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(player_ped, weapon_hash, component);
					WEAPON::GIVE_WEAPON_TO_PED(player_ped, weapon_hash, (WEAPON::GET_MAX_AMMO(player_ped, weapon_hash, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, FALSE); //Mk II weapons require giving the weapon to the player twice for them to work, because reasons.
				}
			}
		}
		if (loadout.parachutes != 0)
		{
			WEAPON::GIVE_WEAPON_TO_PED(player_ped, GADGET_PARACHUTE, 1, FALSE, FALSE);
			PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX(player, loadout.parachute_tint);
			PLAYER::SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(player, loadout.parachute_pack_tint);
			if (loadout.parachutes == 2)
			{
				PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);
				PLAYER::SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(player, loadout.reserve_pack_tint);
			}
			auto smoke_trail = loadout.smoke_trail;
			if ((smoke_trail[0] + smoke_trail[1] + smoke_trail[2]) != 765) //255 + 255 + 255
			{
				PLAYER::SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(player, TRUE);
				PLAYER::SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(player, smoke_trail[0], smoke_trail[1], smoke_trail[2]);
			}
		}
	}
}
