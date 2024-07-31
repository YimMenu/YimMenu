#include "gta_util.hpp"
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
			scripts::start_launcher_script("AM_HOT_TARGET"_J);
		});
		components::button("KILL_LIST"_T, [] {
			scripts::start_launcher_script("AM_KILL_LIST"_J);
		});
		components::button("VIEW_NET_MISSIONS_CHECKPOINTS"_T, [] {
			scripts::start_launcher_script("AM_CP_COLLECTION"_J);
		});
		components::button("CHALLENGES"_T, [] {
			scripts::start_launcher_script("AM_CHALLENGES"_J);
		});
		components::button("PENNED_IN"_T, [] {
			scripts::start_launcher_script("AM_PENNED_IN"_J);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("HOT_PROPERTY"_T, [] {
			scripts::start_launcher_script("AM_HOT_PROPERTY"_J);
		});
		components::button("KING_OF_THE_CASTLE"_T, [] {
			scripts::start_launcher_script("AM_KING_OF_THE_CASTLE"_J);
		});
		components::button("CRIMINAL_DAMAGE"_T, [] {
			scripts::start_launcher_script("AM_CRIMINAL_DAMAGE"_J);
		});
		components::button("HUNT_THE_BEAST"_T, [] {
			scripts::start_launcher_script("AM_HUNT_THE_BEAST"_J);
		});
		components::button("BUSINESS_BATTLES"_T, [] {
			scripts::start_launcher_script("BUSINESS_BATTLES"_J);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_ONE_ON_ONE_DEATHMATCH"_T, [] {
			scripts::start_launcher_script("FM_Impromptu_DM_Controler"_J);
		});
		components::button("VIEW_NET_MISSIONS_IMPROMTU_RACE"_T, [] {
			scripts::start_launcher_script("MG_RACE_TO_POINT"_J);
		});
		components::button("FLIGHT_SCHOOL"_T, [] {
			scripts::start_launcher_script("Pilot_School_MP"_J);
		});
		components::button("GOLF"_T, [] {
			scripts::start_launcher_script("golf_mp"_J);
		});
		components::button("TUTORIAL"_T, [] {
			scripts::start_launcher_script("FM_INTRO"_J);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VIEW_NET_MISSIONS_ONLY_WORK_ON_JOINING"_T.data());
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("VIEW_NET_MISSIONS_GUNSLINGER"_T, [] {
			scripts::start_launcher_script("gunslinger_arcade"_J);
		});
		components::button("VIEW_NET_MISSIONS_SPACE_MONKEY"_T, [] {
			scripts::start_launcher_script("ggsm_arcade"_J);
		});
		components::button("VIEW_NET_MISSIONS_WIZARD"_T, [] {
			scripts::start_launcher_script("wizard_arcade"_J);
		});
		components::button("VIEW_NET_MISSIONS_QUB3D"_T, [] {
			scripts::start_launcher_script("puzzle"_J);
		});
		components::button("VIEW_NET_MISSIONS_CAMHEDZ"_T, [] {
			scripts::start_launcher_script("camhedz_arcade"_J);
		});
		ImGui::EndGroup();

		ImGui::Separator();

		if (check_script("am_criminal_damage"_J))
			render_criminal_damage_ui();

		if (check_script("am_cp_collection"_J))
			render_cp_collection_ui();

		if (check_script("am_king_of_the_castle"_J))
			render_king_of_the_castle_ui();

		if (check_script("am_hunt_the_beast"_J))
			render_hunt_the_beast_ui();

		if (!mission_found)
		{
			ImGui::Text("VIEW_NET_MISSIONS_NO_ACTIVE_MISSION"_T.data());
		}
	}
}
