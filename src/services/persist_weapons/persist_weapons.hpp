#pragma once

#include "weaponloadout_json.hpp"

namespace big
{
    class persist_weapons
    {
    public:
		static void save_weapons(std::string loadout_name);
		static void set_weapon_loadout(std::string loadout_name);
		static std::vector<std::string> list_weapon_loadouts();
		static void check_player_has_weapons();
		static void give_player_loadout(std::string loadout_name);
	private:
		static weaponloadout_json get_loadout(std::string loadout_name);
		static big::folder get_weapon_config_folder();
		static void give_Loadout(const weaponloadout_json& loadout);
    };
}
