#include "view_esp.hpp"
#include "pointers.hpp"
#include "services/player_service.hpp"
#include "util/math.hpp"
#include "gta_util.hpp"

namespace big
{
	float esp::calculate_size(rage::fvector3 player_position)
	{
		Vector3 plyr_coords = { player_position.x, player_position.y, player_position.z };
		Vector3 cam_coords = g_pointers->m_get_gamplay_cam_coords();

		float distance = math::distance_between_vectors(plyr_coords, cam_coords);

		return distance > 600.f ? -1.f : 6.17757f / distance;
	}

	void esp::draw() {

		ImGui::SetNextWindowSize({ (float)g->window.x, (float)g->window.y });
		if (ImGui::Begin("draw_window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing))
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			for (auto& item : g_player_service->m_players)
			{
				const std::unique_ptr<player>& plyr = item.second;

				if (plyr->id() == gta_util::get_network_player_mgr()->m_local_net_player->m_player_id || !plyr->is_valid() || plyr->get_ped() == nullptr) continue;

				rage::fvector3& player_pos = plyr->get_ped()->m_navigation->m_position;

				float screen_x;
				float screen_y;

				float multplr = calculate_size(player_pos);

				if (multplr == -1.f) continue;

				if (g_pointers->m_get_screen_coords_for_world_coords(player_pos.data, &screen_x, &screen_y))
				{
					draw_list->AddLine({ (float)g->window.x * 0.5f, (float)g->window.y }, { (float)g->window.x * screen_x, (float)g->window.y * screen_y }, ImColor(0.69f, 0.29f, 0.29f, 1.00f));
					draw_list->AddRect({ (float)g->window.x * screen_x - (62.5f * multplr), (float)g->window.y * screen_y - (175.f * multplr) }, { (float)g->window.x * screen_x - (62.5f * multplr) + (125.f * multplr), (float)g->window.y * screen_y - (175.f * multplr) + (350.f * multplr) }, ImColor(0.69f, 0.29f, 0.29f, 1.00f));
					draw_list->AddText({ (float)g->window.x * screen_x + (67.5f * multplr), (float)g->window.y * screen_y - (175.f * multplr) }, ImColor(0.69f, 0.29f, 0.29f, 1.00f), plyr->get_name());
				}

			}

			ImGui::End();
		}
	}
}