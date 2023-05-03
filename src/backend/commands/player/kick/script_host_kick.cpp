#include "script_host_kick.hpp"

namespace big
{
	CommandAccessLevel script_host_kick::get_access_level()
	{
		return CommandAccessLevel::TOXIC;
	}

	void script_host_kick::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		if (!scripts::force_host(RAGE_JOAAT("freemode")))
		{
			g_notification_service->push_error("Kick", "Force script host failed!");
			return;
		}

		*scr_globals::gsbd_kicking.at(player->id(), 1).as<bool*>() = true;
	}
}
