#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	class send_fake_ban_message : player_command
	{
		union send_fake_ban_message_args {
			struct
			{
				int64_t event;
				int64_t id;
				int64_t playerId;
			};
			char message[15]; // if (HUD::GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(sParam1) > 15) return;
		};

		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			const int arg_count             = 9;
			const char* const str           = "HUD_ROSBANPERM";
			send_fake_ban_message_args args = {(int64_t)eRemoteEvent::SendTextLabelSMS, self::id, 1 << player->id()};
			std::memcpy(args.message, str, std::strlen(str) + 1);

			g_pointers->m_gta.m_trigger_script_event(1, (int64_t*)&args, arg_count, 1 << player->id(), (int)eRemoteEvent::SendTextLabelSMS);
		}
	};

	send_fake_ban_message g_send_fake_ban_message("fakeban", "FAKE_BAN_MESSAGE", "FAKE_BAN_MESSAGE_DESC", 0);
}