#include "send_sext.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	static constexpr auto strippers = std::to_array({"HCH", "INF", "JUL", "NIK", "SAP", "TXI"});

	static constexpr auto sext_types = std::to_array({"1ST", "2ND", "NEED"});

	CommandAccessLevel send_sext::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void send_sext::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		const size_t arg_count  = 8;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::SendTextLabelSMS, self::id};

		strcpy((char*)&args[2],
		    (std::string("SXT_") + strippers[rand() % strippers.size()] + "_" + sext_types[rand() % sext_types.size()]).data());
		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}
}
