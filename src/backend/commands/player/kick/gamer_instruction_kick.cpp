#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "packet.hpp"
#include "gta_util.hpp"

#include <network/Network.hpp>

namespace big
{
	class gamer_instruction_kick : player_command
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
			packet msg;
			msg.write_message(rage::eNetMessage::MsgTransitionGamerInstruction);
			gamer_handle_serialize(g_player_service->get_selected()->get_net_data()->m_gamer_handle_2, msg.m_buffer); // src
			gamer_handle_serialize(g_player_service->get_selected()->get_net_data()->m_gamer_handle_2, msg.m_buffer); // target
			msg.write<bool>(false, 1); // string extend
			msg.write<int>(0, 7); // string length
			msg.write<int>(8, 32); // instruction type
			msg.write<int>(0, 32);
			msg.write<int>(0, 32);
			msg.send(g_player_service->get_selected(), gta_util::get_network()->m_transition_session.m_connection_identifier);
		}
	};

	gamer_instruction_kick g_gamer_instruction_kick("gikick", "Gamer Instruction Kick", "This is unlikely to kick menus that block NETWORK_BAIL", 0);
}