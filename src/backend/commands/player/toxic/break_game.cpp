#include "backend/player_command.hpp"
#include "packet.hpp"

namespace big
{
	class break_game : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			packet pack;
			pack.write_message(rage::eNetMessage::MsgRoamingJoinBubbleAck);
			pack.write(0, 2);
			pack.write(10, 4);
			pack.write(0, 6);
			pack.send(player->get_net_game_player()->m_msg_id);
		}
	};

	break_game g_break_game("breakgame", "BREAK_GAME", "BREAK_GAME_DESC", 0);
}