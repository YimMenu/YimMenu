#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"


namespace big
{
	void view::vehicle() {
		ImGui::BeginGroup();
		ImGui::Checkbox("Can Be Targeted", &g->vehicle.is_targetable);
		ImGui::Checkbox("God Mode", &g->vehicle.god_mode);
		ImGui::Checkbox("Horn Boost", &g->vehicle.horn_boost);
		ImGui::Checkbox("Vehicle Jump", &g->vehicle.vehicle_jump);
		ImGui::Checkbox("Instant Brake", &g->vehicle.instant_brake);
		ImGui::Checkbox("Drive On Water", &g->vehicle.drive_on_water);

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

		components::small_text("Proofs");

		if (ImGui::Button("Check all")) {
			g->vehicle.proof_bullet = true;
			g->vehicle.proof_fire = true;
			g->vehicle.proof_collision = true;
			g->vehicle.proof_melee = true;
			g->vehicle.proof_explosion = true;
			g->vehicle.proof_steam = true;
			g->vehicle.proof_drown = true;
			g->vehicle.proof_water = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Uncheck all")) {
			g->vehicle.proof_bullet = false;
			g->vehicle.proof_fire = false;
			g->vehicle.proof_collision = false;
			g->vehicle.proof_melee = false;
			g->vehicle.proof_explosion = false;
			g->vehicle.proof_steam = false;
			g->vehicle.proof_drown = false;
			g->vehicle.proof_water = false;
		}

		ImGui::BeginGroup();

		ImGui::Checkbox("Bullet", &g->vehicle.proof_bullet);
		ImGui::Checkbox("Fire", &g->vehicle.proof_fire);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Collision", &g->vehicle.proof_collision);
		ImGui::Checkbox("Melee", &g->vehicle.proof_melee);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Explosion", &g->vehicle.proof_explosion);
		ImGui::Checkbox("Steam", &g->vehicle.proof_steam);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Drown", &g->vehicle.proof_drown);
		ImGui::Checkbox("Water", &g->vehicle.proof_water);

		ImGui::EndGroup();

		g->vehicle.proof_mask = 0;
		if (g->vehicle.god_mode)
		{
			g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		else
		{
			if (g->vehicle.proof_bullet)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
			}
			if (g->vehicle.proof_fire)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
			}
			if (g->vehicle.proof_collision)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
			}
			if (g->vehicle.proof_melee)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
			}
			if (g->vehicle.proof_explosion)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
			}
			if (g->vehicle.proof_steam)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
			}
			if (g->vehicle.proof_drown)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::DROWN);
			}
			if (g->vehicle.proof_water)
			{
				g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::WATER);
			}
		}

		ImGui::Separator();

		components::small_text("Auto Drive");

		components::button("Drive To Waypoint", [] {

			g->vehicle.auto_drive_to_waypoint = true;
			});

		components::button("Wander", [] {

			g->vehicle.auto_drive_wander = true;
			});

		ImGui::SliderInt("Top Speed", &g->vehicle.auto_drive_speed, 1, 200);

		components::button("E-Stop", [] {

				g->vehicle.auto_drive_to_waypoint = false;
				g->vehicle.auto_drive_wander = false;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
			});

		if (ImGui::ListBox("Driving Style", &g->vehicle.driving_style_id, vehicle::driving_style_names, 2))
		{
			g->vehicle.driving_style_flags = vehicle::driving_styles[g->vehicle.driving_style_id];
			g_notification_service->push_warning("Auto Drive", fmt::format("Driving style set to {}.", vehicle::driving_style_names[g->vehicle.driving_style_id]));
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
	}
}
