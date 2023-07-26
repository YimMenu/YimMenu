#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class trigger_ceo_raid : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 3;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::TriggerCEORaid, (int64_t)self::id, 0};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	trigger_ceo_raid g_trigger_ceo_raid("ceoraid", "TRIGGER_CEO_RAID", "TRIGGER_CEO_RAID_DESC", 0);
}