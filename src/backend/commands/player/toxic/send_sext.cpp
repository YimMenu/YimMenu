#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	static constexpr auto strippers = std::to_array({"HCH", "INF", "JUL", "NIK", "SAP", "TXI"});

	static constexpr auto sext_types = std::to_array({"1ST", "2ND", "NEED"});

	class send_sext : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 8;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::SendTextLabelSMS, self::id};

			strcpy((char*)&args[2],
			    (std::string("SXT_") + strippers[rand() % strippers.size()] + "_" + sext_types[rand() % sext_types.size()])
			        .data());
			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	send_sext g_send_sext("sext", "Send Sext", "Sends a random sext (with an image attachment) to the player", 0);
}