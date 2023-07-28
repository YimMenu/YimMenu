#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class send_to_apartment : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count = 9;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::Teleport, self::id, (int64_t)player->id(), (int64_t)(int)-1, 1, (int64_t)_args.get<int64_t>(0), 1, 1, 1};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	send_to_apartment g_send_to_apartment("apartmenttp", "TP_TO_APARTMENT", "TP_TO_APARTMENT_DESC", 1);
}