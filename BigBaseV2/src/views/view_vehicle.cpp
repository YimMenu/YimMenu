#include "views/view.hpp"
#include "core/data/speedo_meters.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::vehicle() {
		if (ImGui::TreeNode("General"))
		{
			ImGui::BeginGroup();
			ImGui::Checkbox("Can Be Targeted", &g->vehicle.is_targetable);
			ImGui::Checkbox("God Mode", &g->vehicle.god_mode);
			ImGui::Checkbox("Horn Boost", &g->vehicle.horn_boost);
			ImGui::Checkbox("Drive On Water", &g->vehicle.drive_on_water);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			components::button("Repair", [] {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				vehicle::repair(veh);
			});

			if (components::button("Handling")) {
				ImGui::OpenPopup("Handling Popup");
			}

			bool enabled = true;

			ImGui::SetNextWindowSize({ (float)*g_pointers->m_resolution_x * 0.5f, (float)*g_pointers->m_resolution_y * 0.5f }, ImGuiCond_FirstUseEver);
			if (ImGui::BeginPopupModal("Handling Popup", &enabled, ImGuiWindowFlags_MenuBar))
			{
				if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
				{
					ImGui::Text("Please enter a vehicle.");
					ImGui::EndPopup();
					return;
				}
				g_vehicle_service->attempt_save();

				ImGui::BeginTabBar("handling_profiles");
				tab_handling::tab_current_profile();
				tab_handling::tab_my_profiles();
				tab_handling::tab_saved_profiles();
				tab_handling::tab_search();
				ImGui::EndTabBar();

				ImGui::EndPopup();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Paint"))
		{
			ImGui::ListBox("RGB Type", &g->vehicle.rainbow_paint, vehicle::rgb_types, 3);

			if (g->vehicle.rainbow_paint != 0)
			{
				ImGui::SliderInt("RGB Speed", &g->rgb.speed, 1, 10);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("LS Customs"))
		{
			components::button("Start LS Customs", [] {
				g->vehicle.ls_customs = true;
				});

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Speedo Meter"))
		{
			SpeedoMeter selected = g->vehicle.speedo_meter.type;

			ImGui::Text("Type:");
			if (ImGui::BeginCombo("###speedo_type", speedo_meters[(int)selected].name))
			{
				for (const speedo_meter& speedo : speedo_meters)
				{
					if (ImGui::Selectable(speedo.name, speedo.id == selected))
					{
						g->vehicle.speedo_meter.type = speedo.id;
					}

					if (speedo.id == selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			ImGui::Text("Position");

			float pos[2];
			pos[0] = g->vehicle.speedo_meter.x;
			pos[1] = g->vehicle.speedo_meter.y;
			if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
			{
				g->vehicle.speedo_meter.x = pos[0];
				g->vehicle.speedo_meter.y = pos[1];
			}

			ImGui::Checkbox("Left Sided", &g->vehicle.speedo_meter.left_side);

			ImGui::TreePop();
		}
	}
}