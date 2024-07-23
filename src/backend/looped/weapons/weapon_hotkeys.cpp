#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "gui.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	constexpr int input_array[6] = {(int)ControllerInputs::INPUT_SELECT_WEAPON_UNARMED, (int)ControllerInputs::INPUT_SELECT_WEAPON_MELEE, (int)ControllerInputs::INPUT_SELECT_WEAPON_SHOTGUN, (int)ControllerInputs::INPUT_SELECT_WEAPON_HEAVY, (int)ControllerInputs::INPUT_SELECT_WEAPON_SPECIAL, (int)ControllerInputs::INPUT_SELECT_WEAPON_HANDGUN};

	static void resolve_weapon_hotkey(Hash weapon)
	{
		if (g_gta_data_service.weapon_by_hash(weapon).m_name.empty())
		{
			WEAPON::SET_CURRENT_PED_VEHICLE_WEAPON(self::ped, weapon);
		}
		else
		{
			WEAPON::SET_CURRENT_PED_WEAPON(self::ped, weapon, TRUE);
		}
	}

	void looped::weapons_do_weapon_hotkeys()
	{
		Ped player_ped = self::ped;

		if (!g.weapons.enable_weapon_hotkeys || g_gui->is_open() || HUD::IS_PAUSE_MENU_ACTIVE() || PED::IS_PED_DEAD_OR_DYING(player_ped, true) || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() || DLC::GET_IS_LOADING_SCREEN_ACTIVE() || HUD::IS_MP_TEXT_CHAT_TYPING())
		{
			return;
		}

		Hash current_weapon, current_vehicle_weapon;
		WEAPON::GET_CURRENT_PED_WEAPON(player_ped, &current_weapon, false);
		WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(player_ped, &current_vehicle_weapon);
		for (int iterator_keys = 0; iterator_keys < 6; iterator_keys++)
		{
			PAD::DISABLE_CONTROL_ACTION(0, input_array[iterator_keys], FALSE);
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, input_array[iterator_keys]))
			{
				if (!g.weapons.weapon_hotkeys.count(iterator_keys))
					continue;

				auto& hotkey_vector = g.weapons.weapon_hotkeys[iterator_keys];

				if (hotkey_vector.empty())
					continue;

				Hash weapon_hash_to_select = hotkey_vector[0];
				for (auto vector_iterator = hotkey_vector.begin(); vector_iterator != hotkey_vector.end(); ++vector_iterator)
				{
					Hash iteration_hash = *vector_iterator;
					if (current_weapon == iteration_hash || current_vehicle_weapon == iteration_hash)
					{
						if (vector_iterator != hotkey_vector.end() - 1)
						{
							weapon_hash_to_select = *std::next(vector_iterator);
						}
					}
				}
				resolve_weapon_hotkey(weapon_hash_to_select);
			}
		}
	}
}
