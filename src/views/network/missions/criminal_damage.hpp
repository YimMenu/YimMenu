#include "core/scr_globals.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

namespace big
{
	inline void render_criminal_damage_ui()
	{
		components::sub_title("Criminal Damage");
		components::button("Start Event##criminal_damage", [] {
			if (scripts::force_host(RAGE_JOAAT("am_criminal_damage")))
				if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
					*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(43).as<int*>() = 0;
		});
		ImGui::SameLine();
		components::button("Finish Event##criminal_damage", [] {
			if (scripts::force_host(RAGE_JOAAT("am_criminal_damage")))
				if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
					*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(39).as<int*>() = 0;
		});

		components::button("Max Score", [] {
			if (auto criminal_damage = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
				*script_local(criminal_damage->m_stack, scr_locals::am_criminal_damage::score_idx).as<int*>() = 999'999'999;
		});
	}
}