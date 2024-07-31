#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
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
			if (!player || !player->is_valid())
				return;
			if (!scripts::force_host("freemode"_J))
			{
				g_notification_service.push_error("END_KICK"_T.data(), "BACKEND_END_SESSION_KICK_FORCE_SCRIPT_HOST_FAILED"_T.data());
				return;
			}

			player->trigger_end_session_kick = true;
			*scr_globals::gsbd.as<int*>() = (int)(__rdtsc() % 50000) + 6; // making the game trigger the broadcast is a bit difficult and requires a little bit of tampering with the value and some luck
			script::get_current()->yield(5s);
			*scr_globals::gsbd.as<int*>() = 4;
		}
	};

	end_session_kick g_end_session_kick("endkick", "END_KICK", "END_KICK_DESC", 0);
}
