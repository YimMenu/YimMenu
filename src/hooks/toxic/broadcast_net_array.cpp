#include "gta/net_array.hpp"
#include "hooking.hpp"
#include "script_global.hpp"
#include "script_local.hpp"
#include "services/players/player_service.hpp"
#include "util/scripts.hpp"
#include "util/system.hpp"

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

		bool need_to_modify_wanted_level = g.session.wanted_level_all
		    && (_this->m_array >= scr_globals::globalplayer_bd.as<uint8_t*>()
		        && _this->m_array <= scr_globals::globalplayer_bd.at(31, sizeof(GlobalPlayerBDEntry) / 8).as<uint8_t*>());

		bool need_to_turn_player_into_beast = g.m_hunt_the_beast_thread && g.m_hunt_the_beast_thread->m_stack
		    && g.m_hunt_the_beast_thread->m_net_component
		    && _this->m_array
		        == script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).as<void*>();

		bool need_to_randomize_replay_protection =
		    g.session.block_ceo_money && _this->m_array == scr_globals::gsbd_fm_events.as<void*>();

		if (need_to_use_end_session_kick)
		{
			orig_gsbd                          = *scr_globals::gsbd.as<int*>();
			*scr_globals::gsbd.as<uint32_t*>() = 5;
			g_pointers->m_broadcast_patch->apply();
		}

		if (need_to_modify_wanted_level)
		{
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].RemoteWantedLevelPlayer = target->m_player_id;
			g_pointers->m_broadcast_patch->apply();
		}

		if (need_to_turn_player_into_beast)
		{
			orig_player = *script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx)
			                   .at(1)
			                   .at(7)
			                   .as<Player*>();
			orig_participant = *script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx)
			                        .at(1)
			                        .at(6)
			                        .as<int*>();

			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() =
			    g.m_hunt_the_beast_thread->m_net_component->get_participant_index(target);// participant idx
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() =
			    target->m_player_id;// beast player idx
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(2).as<int*>() = INT_MAX;// stopwatch time
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(83).as<int*>() = 0;// transformed bitset

			g_pointers->m_broadcast_patch->apply();
		}

		if (need_to_randomize_replay_protection)
		{
			*scr_globals::gsbd_fm_events.at(9).as<uint32_t*>()  = __rdtsc();
			*scr_globals::gsbd_fm_events.at(10).as<uint32_t*>() = __rdtsc();
			g_pointers->m_broadcast_patch->apply();
		}

		int ret = g_hooking->get_original<hooks::broadcast_net_array>()(_this, target, bit_buffer, counter, elem_start, silent);

		if (need_to_use_end_session_kick)
		{
			g_pointers->m_broadcast_patch->restore();
			*scr_globals::gsbd.as<int*>() = orig_gsbd;
		}

		if (need_to_modify_wanted_level)
		{
			g_pointers->m_broadcast_patch->restore();
		}

		if (need_to_turn_player_into_beast)
		{
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() = orig_player;
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() = orig_participant;
			g_pointers->m_broadcast_patch->restore();
		}

		if (need_to_randomize_replay_protection)
		{
			g_pointers->m_broadcast_patch->restore();
		}

		return ret;
	}
}