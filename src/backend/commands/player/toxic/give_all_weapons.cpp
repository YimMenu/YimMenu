#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	class give_all_weapons : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			for (auto& weapon : g_gta_data_service->weapons())
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
		}
	};

	class give_all_weapons_all : command
	{
		using command::command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			g_player_service->iterate([](auto& plyr) {
				for (auto& weapon : g_gta_data_service->weapons())
					WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr.second->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
				script::get_current()->yield(500ms);
			});
		}
	};

	give_all_weapons g_give_all_weapons("giveweaps", "Give Weapons", "Gives all weapons to the player", 0, false);
	give_all_weapons_all g_give_all_weapons_all("giveweapsall", "Give Weapons", "Gives weapons to everyone. Don't spam this or you will crash", 0);
}