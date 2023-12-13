#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class null_function_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player)
				return;
			const size_t arg_count  = 15;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::InteriorControl, (int64_t)self::id, (int64_t)(int)-1};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::InteriorControl);
		}
	};

	null_function_kick g_null_function_kick("nfkick", "NULL_FUNCTION_KICK", "NULL_FUNCTION_KICK_DESC", 0);
}