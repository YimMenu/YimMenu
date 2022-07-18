#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "util/mobile.hpp"
#include "core/data/speed_units.hpp"

namespace big
{
	int d_speed = 50;
	void view::vehicle()
	{
		components::button("MMI Fix All PV", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				fmt::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});
		ImGui::SameLine();
		components::button("Repair", [] {
			vehicle::repair(self::veh);
		});

		ImGui::Separator();

		components::button("Teleport in PV", [] {
			Vehicle veh = globals::get_personal_vehicle();
			teleport::into_vehicle(veh);
		});
		ImGui::SameLine();
		components::button("Bring PV", [] {
			Vehicle veh = globals::get_personal_vehicle();
			vehicle::bring(veh, self::pos, true);
		});
		ImGui::SameLine();
		components::button("Bring Closest Vehicle", [] {
			Vehicle veh = vehicle::get_closest_to_location(self::pos, 200);
			vehicle::bring(veh, self::pos, true, -1);
		});

		ImGui::Separator();

		components::small_text("General");

		ImGui::BeginGroup();
		ImGui::Checkbox("God Mode", &g->vehicle.god_mode);
		ImGui::Checkbox("Horn Boost", &g->vehicle.horn_boost);
		ImGui::Checkbox("Vehicle Jump", &g->vehicle.vehicle_jump);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Instant Brake", &g->vehicle.instant_brake);
		ImGui::Checkbox("Can Be Targeted", &g->vehicle.is_targetable);
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
		ImGui::Checkbox("Turn Signals", &g->vehicle.turn_signals);
		if (g->vehicle.turn_signals)
		{
			ImGui::Checkbox("Fully Automatic Signal", &g->vehicle.auto_turn_signals);
		}

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Proofs");

		if (ImGui::Button("Check all"))
		{
			g->vehicle.proof_bullet = true;
			g->vehicle.proof_fire = true;
			g->vehicle.proof_collision = true;
			g->vehicle.proof_melee = true;
			g->vehicle.proof_explosion = true;
			g->vehicle.proof_steam = true;
			g->vehicle.proof_water = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Uncheck all"))
		{
			g->vehicle.proof_bullet = false;
			g->vehicle.proof_fire = false;
			g->vehicle.proof_collision = false;
			g->vehicle.proof_melee = false;
			g->vehicle.proof_explosion = false;
			g->vehicle.proof_steam = false;
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

		ImGui::Checkbox("Water", &g->vehicle.proof_water);

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Speed Unit");

		ImGui::RadioButton(
			speed_unit_strings[(int)SpeedUnit::KMPH].c_str(), 
			(int*)&g->vehicle.speed_unit, 
			(int)SpeedUnit::KMPH
		);
		ImGui::SameLine();
		ImGui::RadioButton(
			speed_unit_strings[(int)SpeedUnit::MIPH].c_str(), 
			(int*)&g->vehicle.speed_unit, 
			(int)SpeedUnit::MIPH
		);
		ImGui::SameLine();
		ImGui::RadioButton(
			speed_unit_strings[(int)SpeedUnit::MPS].c_str(), 
			(int*)&g->vehicle.speed_unit, 
			(int)SpeedUnit::MPS
		);

		ImGui::Separator();

		components::small_text("Speedo Meter");

		ImGui::Checkbox("Enabled", &g->vehicle.speedo_meter.enabled);

		if (g->vehicle.speedo_meter.enabled)
		{
			ImGui::Text("Position (X, Y)");

			float pos[2] = { g->vehicle.speedo_meter.x, g->vehicle.speedo_meter.y };

			if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
			{
				g->vehicle.speedo_meter.x = pos[0];
				g->vehicle.speedo_meter.y = pos[1];
			}

			ImGui::SameLine();

			ImGui::Checkbox("Left Sided", &g->vehicle.speedo_meter.left_side);
		}

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

		static float max_vehicle_torque = 10.f;
		static float max_vehicle_engine = 10.f;

		if (ImGui::SliderFloat("Vehicle torque", &max_vehicle_torque, 0.f, 6000.f) ||
			ImGui::Button("Apply"))
		{

			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), max_vehicle_torque);

		}

		g->vehicle.proof_mask = 0;
		if (g->vehicle.god_mode)
		{
			g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
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
		if (g->vehicle.proof_water)
		{
			g->vehicle.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
