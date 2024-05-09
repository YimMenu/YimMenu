#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	class smart_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (g_player_service->get_self()->is_host())
			{
				dynamic_cast<player_command*>(command::get("breakup"_J))->call(player, {});
			}
			else
			{
				if (player->is_host())
					dynamic_cast<player_command*>(command::get("oomkick"_J))->call(player, {});
				else
					dynamic_cast<player_command*>(command::get("desync"_J))->call(player, {});
			}
		}
	};

	smart_kick g_smart_kick("smartkick", "SMART_KICK", "SMART_KICK_DESC", 0, false);
}
