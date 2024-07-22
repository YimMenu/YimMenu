#include "backend/player_command.hpp"
#include "pointers.hpp"

namespace big
{
	class kill_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player->get_ped())
				return;

			g_pointers->m_gta.m_send_network_damage(
				g_player_service->get_self()->get_ped(),
			    player->get_ped(),
			    player->get_ped()->m_navigation->get_position(),
			    0,
			    true,
			    "weapon_explosion"_J,
			    10000.0f,
			    2,
			    0,
			    (1 << 4) | 0x80000,
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

	kill_player g_kill_player("kill", "KILL_PLAYER", "KILL_PLAYER_DESC", 0);
}
