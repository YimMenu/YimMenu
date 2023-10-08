#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::SeparatorText("Blips:");
		ImGui::Spacing();

		components::command_button<"waypointtp">({}, "Waypoint");
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "Objective");

		ImGui::SeparatorText("Movement");

		ImGui::Spacing();

		components::small_text("Current coordinates");
		float coords[3] = {self::pos.x, self::pos.y, self::pos.z};
		static float new_location[3];
		static float increment = 1;

		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##currentcoordinates", coords, "%f", ImGuiInputTextFlags_ReadOnly);
		components::button("Copy to custom", [coords] {
			ImGui::SetClipboardText(std::format("X: {:.2f}, Y: {:.2f}, Z: {:.2f}", coords[0], coords[1], coords[2]).c_str());
		});

		ImGui::Spacing();
		ImGui::SeparatorText("Vehicles:");
		ImGui::Spacing();
		components::command_button<"pvtp">();
	}
}
