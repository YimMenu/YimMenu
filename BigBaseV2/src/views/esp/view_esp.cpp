#include "view_esp.hpp"
#include "pointers.hpp"
#include "services/player_service.hpp"
#include "util/math.hpp"

namespace big
{
	float esp::calculate_size(rage::fvector3 player_position)
	{
		Vector3 plyr_coords = { player_position.x, player_position.y, player_position.z };
		Vector3 cam_coords = g_pointers->m_get_gamplay_cam_coords();

		float distance = math::distance_between_vectors(plyr_coords, cam_coords);

		return distance > 600.f ? 0.01f : 6.17757f / distance;
	}

	void esp::draw() {

		ImGui::SetNextWindowSize({ (float)g->window.x, (float)g->window.y });
		if (ImGui::Begin("draw_window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs))
		{
			for (auto& item : g_player_service->m_players)
			{
				const std::unique_ptr<player>& plyr = item.second;

				if (!plyr->is_valid() || plyr->get_ped() == nullptr) continue;

				rage::fvector3& player_pos = plyr->get_ped()->m_navigation->m_position;

				float screen_x;
				float screen_y;

				if (g_pointers->m_get_screen_coords_for_world_coords(player_pos.data, &screen_x, &screen_y))
				{
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
					float multplr = esp::calculate_size(player_pos);
					ImGui::SetNextWindowPos({ (float)g->window.x * screen_x - (50.f * multplr), (float)g->window.y * screen_y - (150.f * multplr)});
					if (ImGui::BeginChildFrame(plyr->id(), { 100.f * multplr, 300.f * multplr }, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs))
					{
						ImGui::EndChildFrame();
					}
					ImGui::PopStyleColor();
					ImGui::PopStyleVar();
				}

			}

			ImGui::End();
		}
	}
}