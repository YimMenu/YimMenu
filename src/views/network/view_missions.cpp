#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"
#include "views/network/missions/hunt_the_beast.hpp"
#include "views/network/missions/king_of_the_castle.hpp"
#include "views/network/missions/cp_collection.hpp"
#include "views/network/missions/criminal_damage.hpp"

namespace big
{
	static bool mission_found = false;

	inline rage::scrThread* check_script(rage::joaat_t hash)
	{
		if (auto thread = gta_util::find_script_thread(hash))
		{
			mission_found = true;
			return thread;
		}

		return nullptr;
	}

	void view::missions()
	{
		mission_found = false;

		components::sub_title("Event Starter");

		ImGui::BeginGroup();
		components::button("Hot Target", [] {
			scripts::start_launcher_script(36);
		});
		components::button("Kill List", [] {
			scripts::start_launcher_script(37);
		});
		components::button("Checkpoints", [] {
			scripts::start_launcher_script(39);
		});
		components::button("Challenges", [] {
			scripts::start_launcher_script(40);
		});
		components::button("Penned In", [] {
			scripts::start_launcher_script(41);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Hot Property", [] {
			scripts::start_launcher_script(43);
		});
		components::button("King Of The Castle", [] {
			scripts::start_launcher_script(45);
		});
		components::button("Criminal Damage", [] {
			scripts::start_launcher_script(46);
		});
		components::button("Hunt The Beast", [] {
			scripts::start_launcher_script(47);
		});
		components::button("Business Battles", [] {
			scripts::start_launcher_script(114);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("One-On-One Deathmatch", [] {
			scripts::start_launcher_script(197);
		});
		components::button("Impromptu Race", [] {
			scripts::start_launcher_script(16);
		});
		components::button("Flight School", [] {
			scripts::start_launcher_script(196);
		});
		components::button("Golf", [] {
			scripts::start_launcher_script(193);
		});
		components::button("Tutorial", [] {
			scripts::start_launcher_script(20);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Only works on joining players");
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Gunslinger", [] {
			scripts::start_launcher_script(211);
		});
		components::button("Space Monkey", [] {
			scripts::start_launcher_script(216);
		});
		components::button("Wizard", [] {
			scripts::start_launcher_script(212);
		});
		components::button("QUB3D", [] {
			scripts::start_launcher_script(217);
		});
		components::button("Camhedz", [] {
			scripts::start_launcher_script(218);
		});
		ImGui::EndGroup();

		ImGui::Separator();

		if (check_script(RAGE_JOAAT("am_criminal_damage")))
			render_criminal_damage_ui();

		if (check_script(RAGE_JOAAT("am_cp_collection")))
			render_cp_collection_ui();

		if (check_script(RAGE_JOAAT("am_king_of_the_castle")))
			render_king_of_the_castle_ui();

		if(check_script(RAGE_JOAAT("am_hunt_the_beast")))
			render_hunt_the_beast_ui();

		if (!mission_found)
		{
			ImGui::Text("No active mission");
		}
	}
}