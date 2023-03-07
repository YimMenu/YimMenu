#include "core/data/speed_units.hpp"
#include "fiber_pool.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	void view::vehicle()
	{
		components::button("MORS_FIX_ALL"_T, [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("MOBILE"_T.data(),
			    std::vformat("VEHICLE_FIX_AMOUNT"_T.data(),
			        std::make_format_args(amount_fixed,
			            amount_fixed == 1 ? "VEHICLE_FIX_HAS"_T.data() : "VEHICLE_FIX_HAVE"_T.data())));
		});
		ImGui::SameLine();
		components::button("REPAIR"_T, [] {
			vehicle::repair(self::veh);
		});

		ImGui::SameLine();
		components::command_checkbox<"keepfixed">();

		ImGui::Separator();

		components::button("TP_IN_PV"_T, [] {
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			teleport::into_vehicle(veh);
		});
		ImGui::SameLine();
		components::button("BRING_PV"_T, [] {
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			vehicle::bring(veh, self::pos, true);
		});
		ImGui::SameLine();
		components::button("BRING_CLOSEST_VEHICLE"_T, [] {
			Vehicle veh = vehicle::get_closest_to_location(self::pos, 200);
			vehicle::bring(veh, self::pos, true, -1);
		});

		ImGui::Separator();

		components::button("TURN_ENGINE_ON"_T, [] {
			vehicle::set_engine_state(self::veh, true, g.vehicle.change_engine_state_immediately, g.vehicle.disable_engine_auto_start);
		});
		ImGui::SameLine();
		components::button("TURN_ENGINE_OFF"_T, [] {
			vehicle::set_engine_state(self::veh, false, g.vehicle.change_engine_state_immediately, g.vehicle.disable_engine_auto_start);
		});
		ImGui::Checkbox("DISABLE_ENGINE_AUTO_START"_T.data(), &g.vehicle.disable_engine_auto_start);
		ImGui::SameLine();
		ImGui::Checkbox("CHANGE_STATE_IMMEDIATELY"_T.data(), &g.vehicle.change_engine_state_immediately);

		ImGui::Separator();

		components::sub_title("GENERAL"_T);
		{
			ImGui::BeginGroup();

			ImGui::Checkbox("GOD_MODE"_T.data(), &g.vehicle.god_mode);
			components::command_checkbox<"hornboost">();
			components::command_checkbox<"vehjump">();
			components::command_checkbox<"invisveh">();
			if (g.vehicle.vehinvisibility)
			{
				components::command_checkbox<"localinvisveh">();
			}
			components::command_checkbox<"vehnocollision">();
			components::command_checkbox<"vehallweapons">();

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			components::command_checkbox<"instantbrake">();
			components::command_checkbox<"blockhoming">();
			components::command_checkbox<"driveonwater">();

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			components::command_checkbox<"seatbelt">();
			ImGui::Checkbox("TURN_SIGNALS"_T.data(), &g.vehicle.turn_signals);
			if (g.vehicle.turn_signals)
			{
				ImGui::Checkbox("FULLY_AUTOMATIC_SIGNAL"_T.data(), &g.vehicle.auto_turn_signals);
			}
			components::command_checkbox<"driveunder">();
			components::command_checkbox<"keeponground">();

			ImGui::EndGroup();
		}
		ImGui::Separator();


		components::sub_title("PROOFS"_T);
		{
			if (ImGui::Button("CHECK_ALL"_T.data()))
			{
				g.vehicle.proof_bullet    = true;
				g.vehicle.proof_fire      = true;
				g.vehicle.proof_collision = true;
				g.vehicle.proof_melee     = true;
				g.vehicle.proof_explosion = true;
				g.vehicle.proof_steam     = true;
				g.vehicle.proof_water     = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("UNCHECK_ALL"_T.data()))
			{
				g.vehicle.proof_bullet    = false;
				g.vehicle.proof_fire      = false;
				g.vehicle.proof_collision = false;
				g.vehicle.proof_melee     = false;
				g.vehicle.proof_explosion = false;
				g.vehicle.proof_steam     = false;
				g.vehicle.proof_water     = false;
			}

			ImGui::BeginGroup();

			ImGui::Checkbox("BULLET"_T.data(), &g.vehicle.proof_bullet);
			ImGui::Checkbox("FIRE"_T.data(), &g.vehicle.proof_fire);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("COLLISION"_T.data(), &g.vehicle.proof_collision);
			ImGui::Checkbox("MELEE"_T.data(), &g.vehicle.proof_melee);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("EXPLOSION"_T.data(), &g.vehicle.proof_explosion);
			ImGui::Checkbox("STEAM"_T.data(), &g.vehicle.proof_steam);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("WATER"_T.data(), &g.vehicle.proof_water);

			ImGui::EndGroup();
		}
		ImGui::Separator();


		components::sub_title("SPEED_UNIT"_T);
		{
			ImGui::RadioButton(speed_unit_strings[(int)SpeedUnit::KMPH].c_str(), (int*)&g.vehicle.speed_unit, (int)SpeedUnit::KMPH);
			ImGui::SameLine();
			ImGui::RadioButton(speed_unit_strings[(int)SpeedUnit::MIPH].c_str(), (int*)&g.vehicle.speed_unit, (int)SpeedUnit::MIPH);
			ImGui::SameLine();
			ImGui::RadioButton(speed_unit_strings[(int)SpeedUnit::MPS].c_str(), (int*)&g.vehicle.speed_unit, (int)SpeedUnit::MPS);
		}
		ImGui::Separator();

		components::sub_title("SPEEDO_METER"_T);
		{
			ImGui::Checkbox("ENABLED"_T.data(), &g.vehicle.speedo_meter.enabled);

			if (g.vehicle.speedo_meter.enabled)
			{
				ImGui::Text("POS_X_Y"_T.data());

				float pos[2] = {g.vehicle.speedo_meter.x, g.vehicle.speedo_meter.y};

				if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
				{
					g.vehicle.speedo_meter.x = pos[0];
					g.vehicle.speedo_meter.y = pos[1];
				}

				ImGui::SameLine();

				ImGui::Checkbox("LEFT_SIDED"_T.data(), &g.vehicle.speedo_meter.left_side);
			}
		}

		g.vehicle.proof_mask = 0;
		if (g.vehicle.god_mode)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g.vehicle.proof_bullet)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g.vehicle.proof_fire)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g.vehicle.proof_collision)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g.vehicle.proof_melee)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g.vehicle.proof_explosion)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g.vehicle.proof_steam)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g.vehicle.proof_water)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
