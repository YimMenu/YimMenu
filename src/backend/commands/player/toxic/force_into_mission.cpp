#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class force_into_mission : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 3;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::ForceMission, (int64_t)self::id, 0};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	force_into_mission g_force_into_mission("mission", "Force Into Mission", "Forces the player into a gunrunning mission", 0);
}