#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "features.hpp"
#include "views/view.hpp"


namespace big
{
	int d_speed = 50;
	void view::vehicle() {
		ImGui::BeginGroup();
		ImGui::Checkbox("Can Be Targeted", &g->vehicle.is_targetable);
		ImGui::Checkbox("God Mode", &g->vehicle.god_mode);
		ImGui::Checkbox("Horn Boost", &g->vehicle.horn_boost);
		ImGui::Checkbox("Instant Brake", &g->vehicle.instant_brake);
		ImGui::Checkbox("Drive On Water", &g->vehicle.drive_on_water);
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

		ImGui::Checkbox("Seatbelt", &g->vehicle.seatbelt);

		components::button("Repair", [] {
			vehicle::repair(self::veh);
		});

		components::button("Instant in personal vehicle", [] {
			if (!*g_pointers->m_is_session_started) return g_notification_service->push_warning("WARNING", "Go into GTA V Online to use this option");

			vehicle::go_into_personal_vehicle();
		});

		if (ImGui::TreeNode("Paint"))
		{
			ImGui::ListBox("RGB Type", &g->vehicle.rainbow_paint, vehicle::rgb_types, 3);

			if (g->vehicle.rainbow_paint)
			{
				ImGui::SliderInt("RGB Speed", &g->rgb.speed, 1, 10);
			}

			ImGui::TreePop();
		}

		ImGui::Checkbox("Turn Signals", &g->vehicle.turn_signals);

		if (g->vehicle.turn_signals)
		{
			ImGui::Checkbox("Fully Automatic Signal", &g->vehicle.auto_turn_signals);
		}

		ImGui::EndGroup();

		ImGui::Separator();

		if (ImGui::TreeNode("Auto-Pilot"))
		{
			ImGui::SliderInt("##d_speed", &d_speed, 20, 200);

			ImGui::SameLine();

			ImGui::Text("Driving Speed");

			const char* d_modes[] = { "Normal", "Rush", "Ignore Lights", "Overtake Traffic", "Avoid Traffic", "Avoid More Traffic" };

			static int item_ap = 0;
			ImGui::Combo("Driving Mode", &item_ap, d_modes, IM_ARRAYSIZE(d_modes));

			if (ImGui::Button("Start Driving"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int dBehaviour = 0;
					const char* modeName;

					if (PED::IS_PED_SITTING_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)))
					{
						Blip waypointBlip = HUD::GET_FIRST_BLIP_INFO_ID(8);
						Vector3 coord = HUD::GET_BLIP_INFO_ID_COORD(waypointBlip);

						if (HUD::IS_BLIP_ON_MINIMAP(waypointBlip))
						{
							switch (item_ap)
							{
							case 0:
								dBehaviour = 786603;
								modeName = "Normal";
								break;
							case 1:
								dBehaviour = 1074528293;
								modeName = "Rush";
								break;
							case 2:
								dBehaviour = 2883621;
								modeName = "Ignore Lights";
								break;
							case 3:
								dBehaviour = 5;
								modeName = "Overtake Traffic";
								break;
							case 4:
								dBehaviour = 786468;
								modeName = "Avoid Traffic";
								break;
							case 5:
								dBehaviour = 6;
								modeName = "Avoid More Traffic";
								break;
							default:
								dBehaviour = 786603;
								modeName = "Normal";
								break;
							}
							TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), coord.x, coord.y, coord.z, d_speed, dBehaviour, 5.0f);
							notify::display_help_text("Auto-Pilot : Driving To Waypoint.");
						}
						else
						{
							notify::display_help_text("Auto-Pilot : No Waypoint  Set.");
						}
					}
					else
					{
						notify::display_help_text("Auto-Pilot : Player Not In Vehicle.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::SameLine();

			if (ImGui::Button("Stop Driving"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
					notify::display_help_text("Auto-Pilot : Canceled.");
				}QUEUE_JOB_END_CLAUSE
			}
			ImGui::TreePop();
		}

		ImGui::Separator();

		components::small_text("Vehicle Fly");

		ImGui::Checkbox("Enabled", &g->vehicle.fly.enabled);
		ImGui::SameLine();
		ImGui::Checkbox("Disable Collision", &g->vehicle.fly.no_collision);

		ImGui::Checkbox("Don't Stop", &g->vehicle.fly.dont_stop);
		ImGui::SameLine();
		ImGui::Checkbox("Stop On Exit", &g->vehicle.fly.stop_on_exit);

		ImGui::SliderFloat("Speed", &g->vehicle.fly.speed, 1.f, 100.f, "%.0f", 1);

		ImGui::Separator();

		components::small_text("LS Customs");

		components::button("Start LS Customs", [] {
			g->vehicle.ls_customs = true;
			});

		ImGui::Separator();

		components::small_text("Speedo Meter");

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

			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_torque);

		}
		if (ImGui::SliderFloat("Vehicle Engine", &features::max_vehicle_engine, 0.f, 6000.f) ||
			ImGui::Button("Apply"))
		{
			VEHICLE::MODIFY_VEHICLE_TOP_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_engine);
		}
	}
}
