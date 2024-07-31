#include "backend/player_command.hpp"
#include "pointers.hpp"

namespace big
{
	static constexpr auto strippers = std::to_array({"HCH", "INF", "JUL", "NIK", "SAP", "TXI"});

	static constexpr auto sext_types = std::to_array({"1ST", "2ND", "NEED"});

	class send_sext : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			const size_t arg_count  = 9;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::SendTextLabelSMS, self::id, 1 << player->id()};

			strcpy((char*)&args[3],
			    (std::string("SXT_") + strippers[rand() % strippers.size()] + "_" + sext_types[rand() % sext_types.size()])
			        .data());
			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::SendTextLabelSMS);
		}
	};

	send_sext g_send_sext("sext", "SEND_SEXT", "SEND_SEXT_DESC", 0);
}