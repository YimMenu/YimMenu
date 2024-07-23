#include "backend/player_command.hpp"
#include "pointers.hpp"

namespace big
{
	class force_into_mission : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			const size_t arg_count  = 4;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::ForceMission, (int64_t)self::id, 1 << player->id(), 0};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::ForceMission);
		}
	};

	force_into_mission g_force_into_mission("mission", "FORCE_INTO_MISSION", "FORCE_INTO_MISSION_DESC", 0);
}