#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

namespace big
{
	class end_session_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!scripts::force_host(RAGE_JOAAT("freemode")))
			{
				g_notification_service->push_error("Kick", "Force script host failed!");
				return;
			}

			g_player_service->m_player_to_use_end_session_kick = player;
			*scr_globals::gsbd.as<int*>() = (int)(__rdtsc() % 50000) + 6; // making the game trigger the broadcast is a bit difficult and requires a little bit of tampering with the value and some luck
		}
	};

	end_session_kick g_end_session_kick("endkick", "END_KICK", "END_KICK_DESC", 0, false);
}