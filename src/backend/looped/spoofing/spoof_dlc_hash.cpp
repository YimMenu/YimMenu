#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "hooking/hooking.hpp"

namespace big
{
	class copy_current_dlc_hash : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			g.spoofing.dlc_hash = g_hooking->get_original<hooks::get_dlc_hash>()(*g_pointers->m_gta.m_dlc_manager, 0);
		}
	};

	bool_command
	    g_spoof_dlc_hash("spoofdlchash", "SPOOF_DLC_HASH", "SPOOF_DLC_HASH_DESC", g.spoofing.spoof_dlc_hash);
	copy_current_dlc_hash g_copy_current_dlc_hash("storedlchash", "COPY_CURRENT_DLC_HASH", "COPY_CURRENT_DLC_HASH_DESC", 0);
}
