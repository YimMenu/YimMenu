#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	//You didn't group these originally, but literally everything else that looks like this
	//is grouped so guess what

	void view::teleport()
	{
		//Did you forget about that helper function you wrote ALREADY?
		//ImGui::Text("Blips:");
		components::sub_title("Blips");

		ImGui::BeginGroup();
		{
			components::command_button<"waypointtp">({}, "Waypoint");
			components::command_button<"objectivetp">({}, "Objective");

			ImGui::Checkbox("Auto-Teleport To Waypoint", &g.self.auto_tp);

			ImGui::EndGroup();
		}

		//And here too?
		//ImGui::Text("Vehicles:");
		ImGui::Separator();
		components::sub_title("Vehicles");

		ImGui::BeginGroup();
		{
			components::command_button<"lastvehtp">();		
			components::command_button<"bringpv">();		
			components::command_button<"pvtp">();

			ImGui::EndGroup();
		}
	}
}
