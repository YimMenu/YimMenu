#include "gui/tab_bar.hpp"
#include "gta_util.hpp"

namespace big
{
	void tabbar::render_vehicle()
	{
		CPed* ped = gta_util::get_local_ped();

		bool bVehGodMode = ped->m_vehicle == nullptr ? false : (ped->m_vehicle->m_godmode & 0x1) == 0x1;
		if (ImGui::Checkbox("Vehicle God Mode", &bVehGodMode))
			if (ped->m_vehicle != nullptr)
				ped->m_vehicle->m_godmode = bVehGodMode ? 0x1 : 0x0;

		ImGui::Separator();

		if (ImGui::BeginTabItem("Vehicle"))
		{
			if (ImGui::TreeNode("Speedometer"))
			{
				static const char* speedo_options[] = { "None", "km/h", "mph" };
				if (ImGui::BeginCombo("##speedometer", speedo_options[g_settings.options["speedo_type"].get<int64_t>()]))
				{
					for (uint8_t i = 0; i < IM_ARRAYSIZE(speedo_options); i++)
					{
						bool is_selected = (g_settings.options["speedo_type"].get<int64_t>() == i);
						if (ImGui::Selectable(speedo_options[i], is_selected))
						{
							*g_settings.options["speedo_type"].get<int64_t*>() = i;
							g_settings.save();
						}
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Handling"))
			{
				CAutomobile* veh = ped->m_vehicle;

				static float fAcceleration = veh == nullptr ? 1.f : veh->m_handling->m_acceleration;
				if (ImGui::SliderFloat("Acceleration", &fAcceleration, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_acceleration = fAcceleration;

				static float fBrakeForce = veh == nullptr ? 1.f : veh->m_handling->m_brakeforce;
				if (ImGui::SliderFloat("Brake Force", &fBrakeForce, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_brakeforce = fBrakeForce;

				static float fGravity = veh == nullptr ? 1.f : veh->m_gravity;
				if (ImGui::SliderFloat("Gravity", &fGravity, -24.f, 24.f))
					if (veh != nullptr)
						veh->m_gravity = fGravity;

				static float fUpshift = veh == nullptr ? 1.f : veh->m_handling->m_upshift;
				static float fDownShift = veh == nullptr ? 1.f : veh->m_handling->m_downshift;
				if (ImGui::SliderFloat("Upshift", &fUpshift, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_upshift = fUpshift;

				if (ImGui::SliderFloat("Downshift", &fDownShift, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_downshift = fDownShift;

				static float fMass = veh == nullptr ? 1.f : veh->m_handling->m_mass;
				if (ImGui::InputFloat("Mass", &fMass))
					if (veh != nullptr)
						veh->m_handling->m_mass = fMass;

				static float fTractionCurveMax = veh == nullptr ? 1.f : veh->m_handling->m_traction_curve_max;
				static float fTractionCurveMin = veh == nullptr ? 1.f : veh->m_handling->m_traction_curve_min;
				if (ImGui::SliderFloat("Traction Curve Max", &fTractionCurveMax, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_traction_curve_max = fTractionCurveMax;

				if (ImGui::SliderFloat("Traction Curve Min", &fTractionCurveMin, 0.f, 100.f))
					if (veh != nullptr)
						veh->m_handling->m_traction_curve_min = fTractionCurveMin;

				static float fTractionLoss = veh == nullptr ? 1.f : veh->m_handling->m_traction_loss_mult;
				if (ImGui::SliderFloat("Off-Road Traction Loss (lower better)", &fTractionLoss, 0.f, 2.f))
					if (veh != nullptr)
						veh->m_handling->m_traction_loss_mult = fTractionLoss;

				static float fDriveBiasFront = veh == nullptr ? .5f : veh->m_handling->m_drive_bias_front;
				if (ImGui::SliderFloat("Drive Bias Front", &fDriveBiasFront, 0.f, 1.f))
					if (veh != nullptr)
						veh->m_handling->m_drive_bias_front = fDriveBiasFront;

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (ImGui::Button("Auto Pilot"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

					if (!veh)
						features::notify::above_map("~r~Make sure you are in a vehicle.");
					else if (!HUD::DOES_BLIP_EXIST(blipHandle))
						features::notify::above_map("~r~Waypoint needs to be set.");
					else
					{
						Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);
						// Make sure the AI can reach this
						location = features::teleport::get_ground_at_3dcoord(location);

						TASK::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), veh, location.x, location.y, location.z, 35.f, 0, veh, 2883620, 10.f, true);
					}
				}QUEUE_JOB_END_CLAUSE
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop Auto Pilot"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

					Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

					TASK::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), veh, location.x, location.y, location.z, 35.f, 0, veh, 2883620, 10.f, true);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			ImGui::Checkbox("No Bike Fall", g_settings.options["no_bike_fall"].get<bool*>());

			ImGui::Checkbox("Sticky Tyres", g_settings.options["sticky_tyres"].get<bool*>());

			if (ImGui::Button("Repair Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_FIXED(veh);

						features::notify::above_map("Vehicle has been repaired.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Clean Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0);

						features::notify::above_map("Vehicle has been cleaned.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Bullet Proof Tyres"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
					}
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}