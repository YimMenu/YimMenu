#include "backend/player_command.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	class remove_all_weapons : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			for (auto& [_, weapon] : g_gta_data_service.weapons())
				WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), weapon.m_hash);
		}
	};

	remove_all_weapons g_remove_all_weapons("remweaps", "REMOVE_ALL_WEAPONS", "REMOVE_ALL_WEAPONS_DESC", 0);
}
