#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	class multi_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (g_player_service->get_self()->is_host())
				dynamic_cast<player_command*>(command::get("breakup"_J))->call(player, {}),
				    dynamic_cast<player_command*>(command::get("hostkick"_J))->call(player, {});

			dynamic_cast<player_command*>(command::get("oomkick"_J))->call(player, {});
			script::get_current()->yield(700ms);


			if (player && !g_player_service->get_self()->is_host() && player->is_valid() && !player->is_host())
				dynamic_cast<player_command*>(command::get("desync"_J))->call(player, {});
		}
	};

	multi_kick g_multi_kick("multikick", "MULTI_KICK", "MULTI_KICK_DESC", 0, false);
}
