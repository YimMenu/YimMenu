#include "util/ped.hpp"
#include "views/view.hpp"
#include "widgets/imgui_bitfield.hpp"

namespace big
{
	void view::self_fun()
	{
		ImGui::BeginGroup();

		components::command_checkbox<"superherofly">();
		if (g.self.super_hero_fly.enabled)
		{
			ImGui::SameLine();
			ImGui::Checkbox("Gradual speed", &g.self.super_hero_fly.gradual);
			ImGui::SameLine();
			ImGui::Checkbox("Explosions", &g.self.super_hero_fly.explosions);
			ImGui::SameLine();
			ImGui::Checkbox("Auto land", &g.self.super_hero_fly.auto_land);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputFloat("Speed", &g.self.super_hero_fly.fly_speed, 1, 50);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputFloat("Initial launch", &g.self.super_hero_fly.initial_launch, 1, 50);
		}

		components::command_checkbox<"bulletshield">();

		ImGui::EndGroup();
	}
}