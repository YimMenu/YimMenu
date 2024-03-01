#include "views/view.hpp"

namespace big
{
	void view::blackhole()
	{
		components::command_checkbox<"blackhole">();

		ImGui::SeparatorText("VIEW_BLACKHOLE_ENTITIES"_T.data());
		components::command_checkbox<"blackholeincvehs">();
		ImGui::SameLine();
		components::command_checkbox<"blackholeincpeds">();

		ImGui::SeparatorText("VIEW_OVERLAY_POSITION"_T.data());
		ImGui::InputFloat("X", &g.world.blackhole.pos.x, 5.f, 200.f);
		ImGui::InputFloat("Y", &g.world.blackhole.pos.y, 5.f, 200.f);
		ImGui::InputFloat("Z", &g.world.blackhole.pos.z, 5.f, 200.f);
		ImGui::SliderFloat("VIEW_BLACKHOLE_SCALE"_T.data(), &g.world.blackhole.scale, 2.f, 12.f, "%.0f");

		components::button("VIEW_BLACKHOLE_SET"_T, [] {
			if (g_local_player)
			{
				const auto player_pos = g_local_player->get_position();

				g.world.blackhole.pos.x = player_pos->x;
				g.world.blackhole.pos.y = player_pos->y;
				g.world.blackhole.pos.z = player_pos->z;
			}
		});

		ImGui::SeparatorText("VIEW_BLACKHOLE_CUSTOM"_T.data());
		ImGui::SetNextItemWidth(214);
		ImGui::ColorPicker3("VIEW_BLACKHOLE_COLOR"_T.data(), g.world.blackhole.color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex);
		ImGui::SliderInt("VIEW_BLACKHOLE_ALPHA"_T.data(), &g.world.blackhole.alpha, 0, 255);
	}
}