#include "core/data/ipls.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::SeparatorText("BLIPS"_T.data());
		ImGui::Spacing();

		components::command_button<"waypointtp">({}, "VIEW_PLAYER_TELEPORT_WAYPOINT"_T);
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "VIEW_TELEPORT_OBJECTIVE"_T);
		ImGui::SameLine();
		components::command_button<"highlighttp">({}, "VIEW_TELEPORT_SELECTED"_T);
		components::command_checkbox<"autotptowp">();

		ImGui::SeparatorText("VIEW_TELEPORT_MOVEMENT"_T.data());

		ImGui::Spacing();

		components::small_text("VIEW_TELEPORT_CURRENT_COORDINATES"_T);
		float coords[3] = {self::pos.x, self::pos.y, self::pos.z};
		static float new_location[3];
		static float increment = 1;

		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##currentcoordinates", coords, "%f", ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		components::button("VIEW_TELEPORT_COPY_TO_CUSTOM"_T, [coords] {
			std::copy(std::begin(coords), std::end(coords), std::begin(new_location));
		});

		components::small_text("GUI_TAB_CUSTOM_TELEPORT"_T);
		ImGui::SetNextItemWidth(400);
		ImGui::InputFloat3("##Customlocation", new_location);
		ImGui::SameLine();
		components::button("GUI_TAB_TELEPORT"_T, [] {
			teleport::to_coords({new_location[0], new_location[1], new_location[2]});
		});

		ImGui::Spacing();
		components::small_text("VIEW_TELEPORT_SPECIFIC_MOVEMENT"_T);
		ImGui::Spacing();

		ImGui::SetNextItemWidth(200);
		ImGui::InputFloat("VIEW_SELF_CUSTOM_TELEPORT_DISTANCE"_T.data(), &increment);

		ImGui::BeginGroup();
		components::button("VIEW_TELEPORT_FORWARD"_T, [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, increment, 0));
		});
		components::button("VIEW_TELEPORT_BACKWARD"_T, [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, -increment, 0));
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("LEFT"_T, [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, -increment, 0, 0));
		});
		components::button("RIGHT"_T, [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, increment, 0, 0));
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("VIEW_TELEPORT_UP"_T, [] {
			teleport::to_coords(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, increment));
		});
		components::button("VIEW_TELEPORT_DOWN"_T, [] {
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

		static int current_select = 0;
		static int last_select    = -1;

		ImGui::SetNextItemWidth(400);
		if (ImGui::BeginCombo("##Ipllocation", ipls[current_select].friendly_name))
		{
			for (int i = 0; i < IM_ARRAYSIZE(ipls); i++)
			{
				bool is_selected = (i == current_select);
				if (ImGui::Selectable(ipls[i].friendly_name, is_selected))
				{
					current_select = i;
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();
		components::button("LOAD_IPL"_T, [] 
		{
			// If we've changed selections, first unload previously loaded IPL, then load previously deleted IPLs
			if (current_select != last_select)
			{
				// Unload previously loaded IPL of the last selection
				// If this is our first time loading an IPL (especially the first one in the list, then don't unload anything)
				if (last_select != -1)
				{
					for (auto& ipl_name_unload : ipls[last_select].ipl_names)
					{
						if (STREAMING::IS_IPL_ACTIVE(ipl_name_unload))
						{
							STREAMING::REMOVE_IPL(ipl_name_unload);
						}
					}

					// Load previously deleted IPLs of the last selection
					for (auto& ipl_name_load : ipls[last_select].ipl_names_remove)
					{
						STREAMING::REQUEST_IPL(ipl_name_load);
					}
				}

				// Load new IPLs of the current selection
				for (auto& ipl_name : ipls[current_select].ipl_names)
				{
					STREAMING::REQUEST_IPL(ipl_name);
				}

				// Remove old IPLs of the current selection to avoid conflicts
				for (auto& ipl_name_remove : ipls[current_select].ipl_names_remove_when_load)
				{
					STREAMING::REMOVE_IPL(ipl_name_remove);
				}

				last_select = current_select;
			}
		});
		ImGui::SameLine();
		components::button("TP_TO_IPL"_T, [] 
		{
			teleport::to_coords(ipls[current_select].location);
		});

		ImGui::Spacing();
		components::small_text("IPL_INFOS"_T);

		auto ipls_data = ipls[current_select].ipl_names.size();

		ImGui::Text(std::vformat("IPL_CNT"_T, std::make_format_args(ipls_data)).data());
		ImGui::Text(std::vformat("IPL_POSITION"_T, std::make_format_args(ipls[current_select].location.x, ipls[current_select].location.y, ipls[current_select].location.z)).data());
	}
}
