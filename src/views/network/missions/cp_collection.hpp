#include "views/view.hpp"
#include "gta_util.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"

namespace big
{
	inline void render_cp_collection_ui()
	{
		components::sub_title("Checkpoints");

		components::button("Start Event##cp_collection", [] {
			if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
				if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
					*script_local(script->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(667).as<int*>() = 0;
		});
		ImGui::SameLine();
		components::button("Finish Event##cp_collection", [] {
			if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
				if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
					*script_local(script->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(661).as<int*>() = 0;
		});

		components::button("Win Event", [] {
			if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
				*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::player_broadcast_idx)
				     .at(checkpoints->m_net_component->m_local_participant_index, 5)
				     .at(4)
				     .as<int*>() = 999'999'999;

			script::get_current()->yield(1s);

			if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
			{
				if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
				{
					*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(708).as<int*>() = 0;
				}
			}
		});
		ImGui::SameLine();
		components::button("Scramble Checkpoints", [] {
			std::vector<Vector3> active_player_positions;

			for (auto& plyr : g_player_service->players())
			{
				if (plyr.second->is_valid() && NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(plyr.second->id(), "am_cp_collection", -1))
				{
					active_player_positions.push_back(
					    ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr.second->id()), false));
				}
			}

			if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
			{
				if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
				{
					for (int i = 0; i < 100; i++)
					{
						*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(10).at(i, 5).as<Vector3*>() =
						    active_player_positions[i % active_player_positions.size()];
					}
				}
			}
		});
	}
}