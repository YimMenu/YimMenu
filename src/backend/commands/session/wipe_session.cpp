#include "backend/player_command.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class wipe_session : command
	{
		using command::command;
		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			g_notification_service->push_warning("Kick All Players From Session", "Starting...");
			g_player_service->iterate([](auto& plyr) {
				if (g_player_service->get_self()->is_host())
				{
					dynamic_cast<player_command*>(command::get(RAGE_JOAAT("breakup")))->call(plyr.second, {});
				}
				else
				{
					dynamic_cast<player_command*>(command::get(RAGE_JOAAT("nfkick")))->call(plyr.second, {});
					dynamic_cast<player_command*>(command::get(RAGE_JOAAT("endkick")))->call(plyr.second, {});
				}
			});
			g_notification_service->push_success("Kick All Players From Session", "Completed!");
		}
	};
	wipe_session g_wipe_session("kicksession", "Kick All Players From Session", "Kicks everyone from the lobby", 0);
}