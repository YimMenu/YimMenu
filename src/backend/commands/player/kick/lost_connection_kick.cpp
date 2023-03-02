#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "packet.hpp"
#include "pointers.hpp"

#include <network/Network.hpp>

namespace big
{
	class lost_connection_kick : player_command
	{
		using player_command::player_command;

		void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
		{
			buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(&hnd.m_platform), 8);
			if (*reinterpret_cast<uint8_t*>(&hnd.m_platform) == 3)
			{
				buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
				buf.Write<uint8_t>(hnd.unk_0009, 8);
			}
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (gta_util::get_network()->m_game_session_ptr->is_host())
			{
				g_notification_service->push_error("Kick", "Cannot use the lost connection kick while host");
				return;
			}

			packet msg{};
			msg.write_message(rage::eNetMessage::MsgLostConnectionToHost);
			msg.write<uint64_t>(gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id, 64);
			gamer_handle_serialize(player->get_net_data()->m_gamer_handle, msg);
			for (auto& [_, plyr] : g_player_service->players())
			{
				if (plyr->is_host())
				{
					msg.send(plyr->get_session_player()->m_msg_id);
					break;
				}
			}
		}
	};

	lost_connection_kick g_lost_connection_kick("lckick", "Lost Connection Kick", "Can only be detected or blocked by the host. Does not work when you are the host, use Host Kick instead", 0);
}