#include "end_session_kick.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"
namespace big
{
	CommandAccessLevel end_session_kick::get_access_level()
	{
		return CommandAccessLevel::TOXIC;
	}

	void end_session_kick::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		if (!scripts::force_host(RAGE_JOAAT("freemode")))
		{
			g_notification_service->push_error("Kick", "Force script host failed!");
			return;
		}

		g_player_service->m_player_to_use_end_session_kick = player;

		// making the game trigger the broadcast is a bit difficult and requires a little bit of tampering with the value and luck
		*scr_globals::gsbd.as<int*>() = (int)(__rdtsc() % 50000) + 6;
	}
}
