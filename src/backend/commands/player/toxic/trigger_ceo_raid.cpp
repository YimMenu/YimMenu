#include "trigger_ceo_raid.hpp"

#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	CommandAccessLevel trigger_ceo_raid::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void trigger_ceo_raid::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		const size_t arg_count  = 3;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::TriggerCEORaid, (int64_t)self::id, 0};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}
}
