#include "gta/net_array.hpp"
#include "hooking.hpp"
#include "script_global.hpp"
#include "script_local.hpp"
#include "services/players/player_service.hpp"
#include "util/scripts.hpp"

#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	unsigned int hooks::broadcast_net_array(rage::netArrayHandlerBase* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent)
	{
		int orig_gsbd;

		Player orig_player;
		int orig_participant;

		bool need_to_use_end_session_kick = g_player_service->m_player_to_use_end_session_kick
		    && target->m_player_id == g_player_service->m_player_to_use_end_session_kick->get()->id()
		    && _this->m_array == scr_globals::gsbd.as<void*>();
	
		if (need_to_use_end_session_kick)
		{
			orig_gsbd                          = *scr_globals::gsbd.as<int*>();
			*scr_globals::gsbd.as<uint32_t*>() = 5;
			broadcast_net_array::m_patch->apply();
		}

		int ret = g_hooking->get_original<hooks::broadcast_net_array>()(_this, target, bit_buffer, counter, elem_start, silent);

		if (need_to_use_end_session_kick)
		{
			broadcast_net_array::m_patch->restore();
			*scr_globals::gsbd.as<int*>() = orig_gsbd;
		}

		return ret;
	}
}