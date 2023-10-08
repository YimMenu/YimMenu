#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::vehicle()
	{
		ImGui::Spacing();
		{
			components::button("Mors Mutual Fix All Vehicles", [] {
				int amount_fixed = mobile::mors_mutual::fix_all();
				g_notification_service->push_success("Mobile", std::vformat("{} vehicle{} been fixed.", std::make_format_args(amount_fixed, amount_fixed == 1 ? " has" : "s have")));
			});
			ImGui::SameLine();
			components::button("Repair", [] {
				vehicle::repair(self::veh);
			});
			ImGui::SameLine();
			components::button("Delete Current", [] {
				if (ENTITY::DOES_ENTITY_EXIST(self::veh))
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped), entity::delete_entity(self::veh);
			});
		}
		ImGui::SeparatorText("###General");
		{
			ImGui::BeginGroup();
			{
				components::command_checkbox<"vehgodmode">();
				components::command_checkbox<"vehjump">();
				components::command_checkbox<"blockhoming">();
				components::command_checkbox<"keepengine">();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				components::command_checkbox<"seatbelt">();
				components::command_checkbox<"veh_boost">();
				components::command_checkbox<"allvehsinheists">();
			}
			ImGui::EndGroup();
		}
	}
}
