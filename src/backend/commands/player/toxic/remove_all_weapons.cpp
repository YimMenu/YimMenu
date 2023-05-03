#include "remove_all_weapons.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	CommandAccessLevel remove_all_weapons::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void remove_all_weapons::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		for (auto& [_, weapon] : g_gta_data_service->weapons())
			WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), weapon.m_hash);
	}
}
