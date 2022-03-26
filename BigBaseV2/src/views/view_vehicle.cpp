#include "views/view.hpp"
#include "core/data/speedo_meters.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "features.hpp"

namespace big
{
	void view::vehicle() {
		if (ImGui::TreeNode("General"))
		{
			ImGui::BeginGroup();
			ImGui::Checkbox("Can Be Targeted", &g->vehicle.is_targetable);
			ImGui::Checkbox("God Mode", &g->vehicle.god_mode);
			ImGui::Checkbox("Horn Boost", &g->vehicle.horn_boost);
			if (ImGui::Button("Gift vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);

						while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
							script::get_current()->yield(10ms);

						DECORATOR::DECOR_REGISTER("PV_Slot", 3);
						DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
						DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
						DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()));
						VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
						notify::above_map("Vehicle Gifted");
					});
			}

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

			ImGui::SetNextWindowSize({ (float)g->window.x * 0.5f, (float)g->window.y * 0.5f }, ImGuiCond_FirstUseEver);
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

			ImGui::EndGroup();

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

			static float max_vehicle_speed = 300.f;
			if (ImGui::SliderFloat("VEHICLE MAX SPEED", &max_vehicle_speed, 0.f, 6000.f))
			{
				Player playerPed = PLAYER::PLAYER_PED_ID();
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(playerPed);

				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);

				while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
					script::get_current()->yield(10ms);

				ENTITY::SET_ENTITY_MAX_SPEED(vehicle, max_vehicle_speed);
			}
			ImGui::Separator();

			if (ImGui::SliderFloat("Vehicle torque", &features::max_vehicle_torque, 0.f, 6000.f) ||
				ImGui::Button("Apply"))
			{

			//	VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_torque);

			}
			if (ImGui::SliderFloat("Vehicle Engine", &features::max_vehicle_engine, 0.f, 6000.f) ||
				ImGui::Button("Apply"))
			{
			//	VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_engine);
			}

			ImGui::TreePop();
		}
	}
}