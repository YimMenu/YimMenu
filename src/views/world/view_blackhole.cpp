#include "views/view.hpp"
#include "util/local_player.hpp"

namespace big
{
	void view::blackhole()
	{
		components::command_checkbox<"blackhole">();

		components::sub_title("Entities");
		ImGui::Checkbox("Vehicles", &g.world.blackhole.include_vehicles);
		ImGui::SameLine();
		ImGui::Checkbox("Peds", &g.world.blackhole.include_peds);

		components::sub_title("Position");
		ImGui::InputFloat("X", &g.world.blackhole.pos.x, 5.f, 200.f);
		ImGui::InputFloat("Y", &g.world.blackhole.pos.y, 5.f, 200.f);
		ImGui::InputFloat("Z", &g.world.blackhole.pos.z, 5.f, 200.f);

		components::button("Set to current coords", [] {
			const auto player_pos = g_local_player->get_position();

			g.world.blackhole.pos.x = player_pos->x;
			g.world.blackhole.pos.y = player_pos->y;
			g.world.blackhole.pos.z = player_pos->z;
		});

		components::sub_title("Customize Hole");
		ImGui::SetNextItemWidth(214);
		ImGui::ColorPicker3("Color", g.world.blackhole.color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex);
		ImGui::SliderInt("Alpha", &g.world.blackhole.alpha, 0, 255);
	}
}