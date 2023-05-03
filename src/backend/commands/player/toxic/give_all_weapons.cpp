#include "give_all_weapons.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	CommandAccessLevel give_all_weapons::get_access_level()
	{
		return CommandAccessLevel::FRIENDLY;
	}

	void give_all_weapons::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		for (auto& weapon : g_gta_data_service->weapons())
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
	}

	CommandAccessLevel give_all_weapons_all::get_access_level()
	{
		return CommandAccessLevel::FRIENDLY;
	}

	void give_all_weapons_all::execute(const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		g_player_service->iterate([](auto& plyr) {
			for (auto& weapon : g_gta_data_service->weapons())
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr.second->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
			script::get_current()->yield(500ms);
		});
	}
}
