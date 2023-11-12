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

		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##currentcoordinates", coords, "%f", ImGuiInputTextFlags_ReadOnly);

		components::button("Copy to custom", [coords] {
			std::copy(std::begin(coords), std::end(coords), std::begin(new_location));
		});
		ImGui::SameLine();
		components::button("Copy to Clipboard", [coords] {
			ImGui::SetClipboardText(std::format("X: {:.2f}, Y: {:.2f}, Z: {:.2f}", coords[0], coords[1], coords[2]).c_str());
		});

		components::small_text("Custom teleport");
		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##Customlocation", new_location);

		components::button("Teleport", [] {
			teleport::to_coords({new_location[0], new_location[1], new_location[2]}, true);
		});
	}
}
