#include "core/data/ipls.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::SeparatorText("BLIPS"_T.data());
		ImGui::Spacing();

		components::command_button<"waypointtp">({}, "Waypoint");
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "Objective");
		ImGui::SameLine();
		components::command_button<"highlighttp">({}, "Selected");
		components::command_checkbox<"autotptowp">();

		ImGui::SeparatorText("Movement");

		ImGui::Spacing();

		components::small_text("Current coordinates");
		float coords[3] = {self::pos.x, self::pos.y, self::pos.z};
		static float new_location[3];
		static float increment = 1;

		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##currentcoordinates", coords, "%f", ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		components::button("Copy to custom", [coords] {
			std::copy(std::begin(coords), std::end(coords), std::begin(new_location));
		});

		components::small_text("Custom teleport");
		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##Customlocation", new_location);
		ImGui::SameLine();
		components::button("Teleport", [] {
			teleport::to_coords({new_location[0], new_location[1], new_location[2]});
		});

		ImGui::Spacing();
		components::small_text("Specific movement");
		ImGui::Spacing();

		ImGui::SetNextItemWidth(200);
		ImGui::InputFloat("Distance", &increment);

		ImGui::BeginGroup();
		components::button("Forward", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, increment, 0));
		});
		components::button("Backward", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, -increment, 0));
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Left", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, -increment, 0, 0));
		});
		components::button("Right", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, increment, 0, 0));
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Up", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, increment));
		});
		components::button("Down", [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, -increment));
		});
		ImGui::EndGroup();

		ImGui::SeparatorText("VEHICLES"_T.data());
		ImGui::Spacing();

		components::command_button<"lastvehtp">();
		ImGui::SameLine();
		components::command_button<"bringpv">();
		ImGui::SameLine();
		components::command_button<"pvtp">();

		ImGui::SeparatorText("GUI_TAB_IPL"_T.data());

		if (ImGui::BeginCombo("IPL_LOCATION"_T.data(), ipls[g.self.ipls.select].friendly_name))
		{
			for (int i = 0; i < IM_ARRAYSIZE(ipls); i++)
			{
				if (ImGui::Selectable(ipls[i].friendly_name, i == g.self.ipls.select))
					g.self.ipls.select = i;

				if (i == g.self.ipls.select)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		const auto& selected_ipl = ipls[g.self.ipls.select];
		if (components::button("LOAD_IPL"_T.data()))
		{
			//unload all previous ipls
			for (auto& ipl : ipls)
				for (auto& ipl_name : ipl.ipl_names)
				{
					if (STREAMING::IS_IPL_ACTIVE(ipl_name))
					{
						LOG(INFO) << "unloading existing ipl " << ipl_name;
						STREAMING::REMOVE_IPL(ipl_name);
					}
				}

			//load the new ipl
			for (auto& ipl_name : selected_ipl.ipl_names)
				STREAMING::REQUEST_IPL(ipl_name);
		}

		ImGui::SameLine();

		if (components::button("TP_TO_IPL"_T.data()))
		{
			teleport::to_coords(selected_ipl.location);
		}

		ImGui::Spacing();
		components::small_text("IPL_INFOS"_T.data());

		ImGui::Text(std::vformat("IPL_CNT"_T, std::make_format_args(selected_ipl.ipl_names.size())).data());
		ImGui::Text(std::vformat("IPL_POSITION"_T,
		    std::make_format_args(selected_ipl.location.x, selected_ipl.location.y, selected_ipl.location.z))
		                .data());
	}
}
