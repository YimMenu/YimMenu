#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "gta/net_game_event.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "packet.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	inline void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		constexpr int PC_PLATFORM = 3;
		buf.Write<uint8_t>(PC_PLATFORM, 8);
		buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
		buf.Write<uint8_t>(hnd.unk_0009, 8);
	}

	bool hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team)
	{
		if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
			command::process(std::string(message + 1), std::make_shared<chat_command_context>(g_player_service->get_self()));

		packet msg{};
		msg.write_message(rage::eNetMessage::MsgTextMessage);
		msg.m_buffer.WriteString(message, 256);
		gamer_handle_serialize(g_player_service->get_self()->get_net_data()->m_gamer_handle, msg.m_buffer);
		msg.write<bool>(is_team, 1);

		for (auto& player : g_player_service->players())
			if (player.second->get_net_game_player())
				msg.send(player.second->get_net_game_player()->m_msg_id);

		return true;

		//return g_hooking->get_original<hooks::send_chat_message>()(team_mgr, local_gamer_info, message, is_team);
	}
}