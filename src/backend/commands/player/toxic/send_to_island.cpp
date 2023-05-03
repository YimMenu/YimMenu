#include "send_to_island.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	CommandAccessLevel send_to_island::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void send_to_island::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		const size_t arg_count  = 2;
		int64_t args[arg_count] = {
		    (int64_t)eRemoteEvent::SendToCayoPerico,
		    (int64_t)self::id,
		};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}
}
