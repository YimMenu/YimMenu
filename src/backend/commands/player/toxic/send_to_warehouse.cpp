#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class send_to_warehouse : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count = 6;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::TeleportToWarehouse, self::id, (int64_t)player->id(), 1, (int64_t)_args.get<int>(0)};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	send_to_warehouse g_send_to_warehouse("warehousetp", "TP_TO_WAREHOUSE", "TP_TO_WAREHOUSE_DESC", 1);
}