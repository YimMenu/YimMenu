#include "views/view.hpp"

namespace big
{
	void view::orbital_drone()
	{
        components::command_checkbox<"orbitaldrone">();

		if (g.world.orbital_drone.enabled)
		{
			ImGui::Separator();
			ImGui::BeginGroup();
			ImGui::Text("press 'Look behind' (C/R3 by default) to activate\npress WASD buttons or Left thumbstick to navigate\nUse scroll wheel/Mouse or Right thumbstick to zoom\npress E/Q or L1/R1 to modify speed\npress 'Jump' (Space/X/Square by default) to lock on an entity\npress 'Fire' (Mouse button 1/Right trigger by default) to Obliterate\npress Enter or A/X by default to teleport to target");
			ImGui::EndGroup();
			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Checkbox("Detect player on lock", &g.world.orbital_drone.detect_player);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("if enabled, changes the selected player to the one it detects upon locking on an entity");
				ImGui::Text("All explosions will be blamed on the selected player, defaulting to the local player");
				ImGui::EndTooltip();
			}
			ImGui::Text("Adjust fast modifier");
			ImGui::SliderFloat("##fastspeed", &g.world.orbital_drone.nav_ovverride_fast, 1.f, 10.f);
			ImGui::Text("Adjust slow modifier");
			ImGui::SliderFloat("##slowspeed", &g.world.orbital_drone.nav_ovverride_slow, 0.f, 1.f);
			ImGui::EndGroup();
		}

	}
}