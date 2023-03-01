#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class kill_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (!player->get_ped())
				return;

			g_pointers->m_send_network_damage((CEntity*)g_player_service->get_self()->get_ped(),
			    (CEntity*)player->get_ped(),
			    player->get_ped()->m_navigation->get_position(),
			    0,
			    true,
			    RAGE_JOAAT("weapon_explosion"),
			    10000.0f,
			    2,
			    0,
			    (1 << 4),
			    0,
			    0,
			    0,
			    false,
			    false,
			    true,
			    true,
			    nullptr);
		}
	};

	kill_player g_kill_player("kill", "Kill Player", "Kills the player, bypassing most forms of interior godmode", 0);
}