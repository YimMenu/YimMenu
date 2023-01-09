#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::Text("Blips:");

		components::command_button<"waypointtp">({}, "Waypoint");
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "Objective");

		ImGui::Checkbox("Auto-Teleport To Waypoint", &g.self.auto_tp);

		ImGui::Text("Vehicles:");
		components::command_button<"lastvehtp">();
		ImGui::SameLine();
		components::command_button<"bringpv">();
		ImGui::SameLine();
		components::command_button<"pvtp">();
	}
}
