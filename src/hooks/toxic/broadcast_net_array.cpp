#include "gta/net_array.hpp"
#include "hooking/hooking.hpp"
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
		int orig_mission_id;
		int orig_mission_plyr;
		int orig_mission_inst;
		bool orig_mission_started;

		int orig_gsbd;

		Player orig_player;
		int orig_participant;

		bool need_to_spoof_mission_data = false;

		auto plyr = g_player_service->get_by_id(target->m_player_id);

		bool need_to_use_end_session_kick = plyr && plyr->is_valid()
		    && plyr->trigger_end_session_kick
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

		if (_this->m_array == scr_globals::gsbd_fm_events.as<void*>())
		{
			// TODO: we don't need this if we can consistently get arrays to sync
			for (auto& player : g_player_service->players())
			{
				if (player.second->script_host_mission.has_value())
				{
					need_to_spoof_mission_data = true;
					break;
				}
			}
		}

		if (need_to_use_end_session_kick)
		{
			orig_gsbd                          = *scr_globals::gsbd.as<int*>();
			*scr_globals::gsbd.as<uint32_t*>() = 5;
			broadcast_net_array::m_patch->apply();
		}

		if (need_to_modify_wanted_level)
		{
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].RemoteWantedLevelPlayer = target->m_player_id;
			broadcast_net_array::m_patch->apply();
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
			    ((CGameScriptHandlerNetComponent*)g.m_hunt_the_beast_thread->m_net_component)->get_participant_index(target);// participant idx
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() =
			    target->m_player_id;// beast player idx
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(2).as<int*>() = INT_MAX;// stopwatch time
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(83).as<int*>() = 0;// transformed bitset

			broadcast_net_array::m_patch->apply();
		}

		if (need_to_randomize_replay_protection)
		{
			*scr_globals::gsbd_fm_events.at(9).as<uint32_t*>()  = __rdtsc();
			*scr_globals::gsbd_fm_events.at(10).as<uint32_t*>() = __rdtsc();
			broadcast_net_array::m_patch->apply();
		}

		if (need_to_spoof_mission_data)
		{
			orig_mission_id = *scr_globals::gsbd_fm_events.at(11).at(144).as<int*>();
			orig_mission_plyr = *scr_globals::gsbd_fm_events.at(11).at(145).as<int*>();
			orig_mission_inst = *scr_globals::gsbd_fm_events.at(11).at(143).as<int*>();
			orig_mission_started = *scr_globals::gsbd_fm_events.at(11).at(146).as<bool*>();

			if (plyr->script_host_mission.has_value())
			{
				*scr_globals::gsbd_fm_events.at(11).at(145).as<int*>() = plyr->id();
				*scr_globals::gsbd_fm_events.at(11).at(144).as<int*>()  = plyr->script_host_mission.value();
				*scr_globals::gsbd_fm_events.at(11).at(146).as<bool*>() = false;
				*scr_globals::gsbd_fm_events.at(11).at(143).as<int*>()  = -1;
			}
			else
			{
				*scr_globals::gsbd_fm_events.at(11).at(146).as<bool*>() = true;
			}
			broadcast_net_array::m_patch->apply();
		}

		int ret = g_hooking->get_original<hooks::broadcast_net_array>()(_this, target, bit_buffer, counter, elem_start, silent);

		if (need_to_use_end_session_kick)
		{
			broadcast_net_array::m_patch->restore();
			*scr_globals::gsbd.as<int*>() = orig_gsbd;
		}

		if (need_to_modify_wanted_level)
		{
			broadcast_net_array::m_patch->restore();
		}

		if (need_to_turn_player_into_beast)
		{
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() = orig_player;
			*script_local(g.m_hunt_the_beast_thread->m_stack, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() = orig_participant;
			broadcast_net_array::m_patch->restore();
		}

		if (need_to_randomize_replay_protection)
		{
			broadcast_net_array::m_patch->restore();
		}

		if (need_to_spoof_mission_data)
		{
			*scr_globals::gsbd_fm_events.at(11).at(144).as<int*>() = orig_mission_id;
			*scr_globals::gsbd_fm_events.at(11).at(145).as<int*>() = orig_mission_plyr;
			*scr_globals::gsbd_fm_events.at(11).at(143).as<int*>() = orig_mission_inst;
			*scr_globals::gsbd_fm_events.at(11).at(144).as<bool*>() = orig_mission_started;
			broadcast_net_array::m_patch->restore();
		}

		return ret;
	}
}