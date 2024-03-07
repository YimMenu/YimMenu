#include "core/scr_globals.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

namespace big
{
	inline void render_criminal_damage_ui()
	{
		components::sub_title("CRIMINAL_DAMAGE"_T);
		ImGui::PushID(2);
		components::button("VIEW_NET_MISSIONS_START_EVENT"_T, [] {
			if (scripts::force_host("am_criminal_damage"_J))
				if (auto script = gta_util::find_script_thread("am_criminal_damage"_J))
					*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(43).as<int*>() = 0;
		});
		ImGui::SameLine();
		components::button("VIEW_NET_MISSIONS_FINISH_EVENT"_T, [] {
			if (scripts::force_host("am_criminal_damage"_J))
				if (auto script = gta_util::find_script_thread("am_criminal_damage"_J))
					*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(39).as<int*>() = 0;
		});
		ImGui::PopID();

		components::button("VIEW_NET_MISSIONS_MAX_SCORE"_T, [] {
			if (auto criminal_damage = gta_util::find_script_thread("am_criminal_damage"_J))
				*script_local(criminal_damage->m_stack, scr_locals::am_criminal_damage::score_idx).as<int*>() = 999'999'999;
		});
	}
}
