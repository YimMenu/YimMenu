#include "core/scr_globals.hpp"
#include "script_local.hpp"
#include "services/tunables/tunables_service.hpp"
#include "util/math.hpp"
#include "util/scripts.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	int get_land_mark_beast_is_closest_to(player_ptr player, script_local land_mark_list, int num_landmarks)
	{
		if (!player->get_ped() || !player->get_ped()->m_navigation)
			return -1;

		int closest_index          = 0;
		Vector3 transformed_vector = Vector3(player->get_ped()->m_navigation->get_position()->x,
		    player->get_ped()->m_navigation->get_position()->y,
		    player->get_ped()->m_navigation->get_position()->z);
		float distance = math::distance_between_vectors(transformed_vector, *land_mark_list.at(0, 3).as<Vector3*>());

		for (int i = 1; i < num_landmarks; i++)
		{
			float new_distance = math::distance_between_vectors(transformed_vector, *land_mark_list.at(i, 3).as<Vector3*>());
			if (new_distance < distance)
			{
				distance      = new_distance;
				closest_index = i;
			}
		}

		return closest_index;
	}

	inline void render_hunt_the_beast_ui()
	{
		if (auto hunt_the_beast_script_thread = gta_util::find_script_thread("am_hunt_the_beast"_J))
		{
			auto beast_player_index =
			    *script_local(hunt_the_beast_script_thread, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<uint32_t*>();
			if (auto beast = g_player_service->get_by_id(beast_player_index))
			{
				ImGui::Text(std::format("{} {}", g_player_service->get_by_id(beast_player_index).get()->get_name(), "VIEW_NET_MISSIONS_IS_THE_BEAST"_T).c_str());
				ImGui::SameLine();
				components::button("VIEW_NET_MISSIONS_SET_AS_SELECTED"_T, [beast] {
					g_player_service->set_selected(beast);
				});

				ImGui::Spacing();

				auto beast_land_mark_list =
				    script_local(hunt_the_beast_script_thread, scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(19);
				static int* num_landmarks = nullptr;

				if (!num_landmarks)
					num_landmarks = g_tunables_service->get_tunable<int*>("HUNT_THE_BEAST_NUMBER_OF_ACTIVE_LANDMARKS"_J);

				if (ImGui::BeginListBox("##beastlandmarks", ImVec2(400, 300)))
				{
					for (int i = 0; i < (num_landmarks ? *num_landmarks : 10); i++)
					{
						auto script_local_land_mark = *beast_land_mark_list.at(i, 3).as<Vector3*>();
						auto label = std::vformat("VIEW_NET_MISSIONS_TP_TO_LANDMARK"_T, std::make_format_args(i, script_local_land_mark.x, script_local_land_mark.y, script_local_land_mark.z));
						if (ImGui::Selectable(label.c_str(), i == get_land_mark_beast_is_closest_to(g_player_service->get_by_id(beast_player_index), beast_land_mark_list, num_landmarks ? *num_landmarks : 10)))
						{
							g_fiber_pool->queue_job([script_local_land_mark, beast] {
								teleport::teleport_player_to_coords(g.player.spectating ? beast : g_player_service->get_self(), script_local_land_mark);
							});
						}
					}
					ImGui::EndListBox();
				}
			}
			else
			{
				ImGui::Text("Hunt the beast event is active...");
			}
		}
	}
}
