#include "view_esp.hpp"

#include "core/settings/esp.hpp"
#include "gta/enums.hpp"
#include "services/players/player_service.hpp"
#include "util/math.hpp"

namespace big
{
	void esp::draw_player(const player_ptr& plyr, ImDrawList* const draw_list)
	{
		if (!plyr->is_valid() || !plyr->get_ped() || !plyr->get_ped()->m_navigation || !plyr->get_ped()->m_model_info)
			return;

		rage::fvector4 player_pos;
		if (!g_pointers->m_gta.m_get_ped_pone(plyr->get_ped(), player_pos, PedBones::SKEL_Pelvis))
			return;

		float screen_x, screen_y;

		const float distance = math::calculate_distance_from_game_cam(player_pos);
		const float multplr  = distance > g_esp.global_render_distance[1] ? -1.f : 6.17757f / distance;

		if (multplr == -1.f || g_esp.global_render_distance[0] > distance)
			return;

		uint32_t ped_damage_bits = plyr->get_ped()->m_damage_bits;

		if (g_pointers->m_gta.m_get_screen_coords_for_world_coords(player_pos.data, &screen_x, &screen_y))
		{
			const auto esp_x = (float)*g_pointers->m_gta.m_resolution_x * screen_x;
			const auto esp_y = (float)*g_pointers->m_gta.m_resolution_y * screen_y;

			std::string name_str = g_esp.name ? plyr->get_name() : std::string(plyr->get_name()).substr(0, 4);
			ImVec2 name_pos      = {esp_x - (62.5f * multplr), esp_y - (175.f * multplr) - 20.f};

			if (g_esp.distance)
				name_str += " | " + std::to_string((int)distance) + "m";

			draw_list->AddText(name_pos, g_esp.default_color, name_str.c_str());
		}
	}

	void esp::draw()
	{
		if (!g_esp.enabled)
			return;

		if (const auto draw_list = ImGui::GetBackgroundDrawList(); draw_list)
			g_player_service->iterate([draw_list](const player_entry& entry) {
				draw_player(entry.second, draw_list);
			});
	}
}