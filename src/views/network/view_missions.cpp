#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/scripts.hpp"
#include "views/network/missions/cp_collection.hpp"
#include "views/network/missions/criminal_damage.hpp"
#include "views/network/missions/hunt_the_beast.hpp"
#include "views/network/missions/king_of_the_castle.hpp"
#include "views/view.hpp"

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

		components::sub_title("VIEW_NET_MISSIONS_EVENT_STARTER"_T);

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_HOT_TARGET"_T, [] {
			scripts::start_launcher_script(36);
		});
		components::button("KILL_LIST"_T, [] {
			scripts::start_launcher_script(37);
		});
		components::button("VIEW_NET_MISSIONS_CHECKPOINTS"_T, [] {
			scripts::start_launcher_script(39);
		});
		components::button("CHALLENGES"_T, [] {
			scripts::start_launcher_script(40);
		});
		components::button("PENNED_IN"_T, [] {
			scripts::start_launcher_script(41);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("HOT_PROPERTY"_T, [] {
			scripts::start_launcher_script(43);
		});
		components::button("KING_OF_THE_CASTLE"_T, [] {
			scripts::start_launcher_script(45);
		});
		components::button("CRIMINAL_DAMAGE"_T, [] {
			scripts::start_launcher_script(46);
		});
		components::button("HUNT_THE_BEAST"_T, [] {
			scripts::start_launcher_script(47);
		});
		components::button("BUSINESS_BATTLES"_T, [] {
			scripts::start_launcher_script(114);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_ONE_ON_ONE_DEATHMATCH"_T, [] {
			scripts::start_launcher_script(216);
		});
		components::button("VIEW_NET_MISSIONS_IMPROMTU_RACE"_T, [] {
			scripts::start_launcher_script(16);
		});
		components::button("FLIGHT_SCHOOL"_T, [] {
			scripts::start_launcher_script(215);
		});
		components::button("GOLF"_T, [] {
			scripts::start_launcher_script(212);
		});
		components::button("TUTORIAL"_T, [] {
			scripts::start_launcher_script(20);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VIEW_NET_MISSIONS_ONLY_WORK_ON_JOINING"_T.data());
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_GUNSLINGER"_T, [] {
			scripts::start_launcher_script(230);
		});
		components::button("VIEW_NET_MISSIONS_SPACE_MONKEY"_T, [] {
			scripts::start_launcher_script(235);
		});
		components::button("VIEW_NET_MISSIONS_WIZARD"_T, [] {
			scripts::start_launcher_script(231);
		});
		components::button("VIEW_NET_MISSIONS_QUB3D"_T, [] {
			scripts::start_launcher_script(236);
		});
		components::button("VIEW_NET_MISSIONS_CAMHEDZ"_T, [] {
			scripts::start_launcher_script(237);
		});
		ImGui::EndGroup();

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_GHOST_HUNT"_T, [] {
			scripts::start_launcher_script(174);
		});
		components::button("VIEW_NET_MISSIONS_POSESSED_ANIMALS"_T, [] {
			scripts::start_launcher_script(179);
		});
		ImGui::EndGroup();

		ImGui::Separator();

		if (check_script(RAGE_JOAAT("am_criminal_damage")))
			render_criminal_damage_ui();

		if (check_script(RAGE_JOAAT("am_cp_collection")))
			render_cp_collection_ui();

		if (check_script(RAGE_JOAAT("am_king_of_the_castle")))
			render_king_of_the_castle_ui();

		if (check_script(RAGE_JOAAT("am_hunt_the_beast")))
			render_hunt_the_beast_ui();

		if (!mission_found)
		{
			ImGui::Text("VIEW_NET_MISSIONS_NO_ACTIVE_MISSION"_T.data());
		}
	}
}