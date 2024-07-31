#include "backend/bool_command.hpp"
#include "services/vehicle/vehicle_control_service.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void render_doors_tab()
	{
		const char* const doornames[MAX_VEHICLE_DOORS]{
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_0"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_1"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_2"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_3"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_4"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_5"_T.data(),
		};

		const char* const locknames[MAX_VEHICLE_LOCK_STATES]{
		    "VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE_NONE"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_1"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_2"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_3"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_4"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_5"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_6"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_7"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_8"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_9"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOCKNAMES_10"_T.data(),
		};

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("##alldoorslock", "VEHICLE_CONTROLLER_ALL_DOORS"_T.data()))
		{
			for (int lockindex = 0; lockindex < MAX_VEHICLE_LOCK_STATES; lockindex++)
			{
				components::selectable(locknames[lockindex], false, [lockindex] {
					g_vehicle_control_service.vehicle_operation([lockindex] {
						vehicle::change_vehicle_door_lock_state(g_vehicle_control_service.m_controlled_vehicle.handle, eDoorId::VEH_EXT_DOOR_INVALID_ID, (eVehicleLockState)lockindex);
					});
				});
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();

		components::button("OPEN_ALL_DOORS"_T, [] {
			g_vehicle_control_service.vehicle_operation([] {
				vehicle::operate_vehicle_door(g_vehicle_control_service.m_controlled_vehicle.handle, eDoorId::VEH_EXT_DOOR_INVALID_ID, true);
			});
		});

		ImGui::SameLine();

		components::button("CLOSE_ALL_DOORS"_T, [] {
			g_vehicle_control_service.vehicle_operation([] {
				vehicle::operate_vehicle_door(g_vehicle_control_service.m_controlled_vehicle.handle, eDoorId::VEH_EXT_DOOR_INVALID_ID, false);
			});
		});

		ImGui::EndGroup();

		ImGui::Separator();

		ImGui::BeginGroup();

		for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
		{
			if (!g_vehicle_control_service.m_controlled_vehicle.doors[i].valid)
				continue;
			ImGui::SetNextItemWidth(200);
			ImGui::PushID(i);
			if (ImGui::BeginCombo(doornames[i], locknames[(int)g_vehicle_control_service.m_controlled_vehicle.doors[i].lock_state]))
			{
				for (int lockindex = 0; lockindex < MAX_VEHICLE_LOCK_STATES; lockindex++)
				{
					components::selectable(locknames[lockindex], false, [i, lockindex] {
						g_vehicle_control_service.vehicle_operation([i, lockindex] {
							vehicle::change_vehicle_door_lock_state(g_vehicle_control_service.m_controlled_vehicle.handle, (eDoorId)i, (eVehicleLockState)lockindex);
						});
					});
				}
				ImGui::EndCombo();
			}

			ImGui::SameLine(300);

			const auto button_label = g_vehicle_control_service.m_controlled_vehicle.doors[i].open ? "CLOSE"_T : "OPEN"_T;
			components::button(button_label, [i] {
				g_vehicle_control_service.vehicle_operation([i] {
					vehicle::operate_vehicle_door(g_vehicle_control_service.m_controlled_vehicle.handle,
					    (eDoorId)i,
					    !g_vehicle_control_service.m_controlled_vehicle.doors[i].open);
				});
			});

			ImGui::PopID();
		}

		ImGui::EndGroup();
	}

	void render_windows_tab()
	{
		const char* const windownames[4]{
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_0"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_1"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_2"_T.data(),
		    "VIEW_VEHICLE_CONTROL_DOOR_NAME_3"_T.data(),
		};

		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SetNextItemWidth(200);
		components::button("VIEW_VEHICLE_CONTROL_ROLL_DOWN_ALL"_T, [] {
			vehicle::operate_vehicle_window(g_vehicle_control_service.m_controlled_vehicle.handle, eWindowId::WINDOW_INVALID_ID, true);
		});
		ImGui::SameLine();
		components::button("VIEW_VEHICLE_CONTROL_ROLL_UP_ALL"_T, [] {
			vehicle::operate_vehicle_window(g_vehicle_control_service.m_controlled_vehicle.handle, eWindowId::WINDOW_INVALID_ID, false);
		});
		ImGui::EndGroup();

		ImGui::Spacing();
		ImGui::Separator();

		ImGui::BeginGroup();
		for (int i = 0; i < 4; i++)
		{
			ImGui::SetNextItemWidth(200);
			ImGui::PushID(i);
			ImGui::Text(windownames[i]);
			ImGui::SameLine(300);
			components::button("VIEW_VEHICLE_CONTROL_ROLL_DOWN"_T, [i] {
				vehicle::operate_vehicle_window(g_vehicle_control_service.m_controlled_vehicle.handle, (eWindowId)i, true);
			});
			ImGui::SameLine();
			components::button("VIEW_VEHICLE_CONTROL_ROLL_UP"_T, [i] {
				vehicle::operate_vehicle_window(g_vehicle_control_service.m_controlled_vehicle.handle, (eWindowId)i, false);
			});
			ImGui::PopID();
		}
	}

	void render_lights_tab()
	{
		const char* const neonnames[4]{
		    "LEFT"_T.data(),
		    "RIGHT"_T.data(),
		    "FRONT"_T.data(),
		    "BACK"_T.data(),
		};

		components::button("VEHICLE_CONTROLLER_TOGGLE_LIGHTS"_T, [] {
			g_vehicle_control_service.vehicle_operation([=] {
				vehicle::operate_vehicle_headlights(g_vehicle_control_service.m_controlled_vehicle.handle,
				    !g_vehicle_control_service.m_controlled_vehicle.headlights,
				    false);
			});
		});

		ImGui::SameLine();
		components::button("VEHICLE_CONTROLLER_TOGGLE_HIGH_BEAMS"_T, [] {
			g_vehicle_control_service.vehicle_operation([=] {
				vehicle::operate_vehicle_headlights(g_vehicle_control_service.m_controlled_vehicle.handle,
				    g_vehicle_control_service.m_controlled_vehicle.headlights,
				    !g_vehicle_control_service.m_controlled_vehicle.highbeams);
			});
		});

		components::button("VEHICLE_CONTROLLER_INTERIOR_LIGHTS_ON"_T, [] {
			g_vehicle_control_service.vehicle_operation([] {
				VEHICLE::SET_VEHICLE_INTERIORLIGHT(g_vehicle_control_service.m_controlled_vehicle.handle, true);
			});
		});

		ImGui::SameLine();

		components::button("VEHICLE_CONTROLLER_INTERIOR_LIGHTS_OFF"_T, [] {
			g_vehicle_control_service.vehicle_operation([] {
				VEHICLE::SET_VEHICLE_INTERIORLIGHT(g_vehicle_control_service.m_controlled_vehicle.handle, false);
			});
		});

		ImGui::Text("VEHICLE_CONTROLLER_NEON_LIGHTS"_T.data());
		ImGui::Separator();

		for (int i = 0; i < 4; i++)
		{
			if (ImGui::Checkbox(neonnames[i], &g_vehicle_control_service.m_controlled_vehicle.neons[i]))
			{
				g_fiber_pool->queue_job([=] {
					g_vehicle_control_service.vehicle_operation([i] {
						vehicle::operate_vehicle_neons(g_vehicle_control_service.m_controlled_vehicle.handle,
						    i,
						    !g_vehicle_control_service.m_controlled_vehicle.neons[i]);
					});
				});
			}
		}
	}

	void render_seats_tab()
	{
		/*
		* Seats start at index -1, compensate accordingly
		*/
		const char* const seatnames[6]{
		    "DRIVER"_T.data(),
		    "VIEW_VEHICLE_CONTROL_PASSENGER"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LEFT_REAR"_T.data(),
		    "VIEW_VEHICLE_CONTROL_RIGHT_REAR"_T.data(),
		    "VIEW_VEHICLE_CONTROL_OUTSIDE_LEFT"_T.data(),
		    "VIEW_VEHICLE_CONTROL_OUTSIDE_RIGHT"_T.data(),
		};

		static int movespeed = 1;

		if (ImGui::RadioButton("VEHICLE_CONTROLLER_ENTER_VEHICLE_SPEED_WALKING"_T.data(), movespeed == 1))
			movespeed = 1;
		ImGui::SameLine();
		if (ImGui::RadioButton("VEHICLE_CONTROLLER_ENTER_VEHICLE_SPEED_RUNNING"_T.data(), movespeed == 2))
			movespeed = 2;
		ImGui::SameLine();
		if (ImGui::RadioButton("VEHICLE_CONTROLLER_ENTER_VEHICLE_SPEED_SPRINTING"_T.data(), movespeed == 3))
			movespeed = 3;

		for (int i = 0; i < 6; i++)
		{
			if (components::button(seatnames[i]))
			{
				g_fiber_pool->queue_job([=] {
					if (g.window.vehicle_control.operation_animation)
						ped::ped_enter_vehicle_animated(self::ped, g_vehicle_control_service.m_controlled_vehicle.handle, (eVehicleSeats)(i - 1), movespeed);
					else
						PED::SET_PED_INTO_VEHICLE(self::ped, g_vehicle_control_service.m_controlled_vehicle.handle, (i - 1));
				});
			}
		}
	}

	void render_misc_tab()
	{
		const char* const convertiblestates[4]{
		    "VIEW_TELEPORT_UP"_T.data(),
		    "VIEW_VEHICLE_CONTROL_LOWERING"_T.data(),
		    "VIEW_TELEPORT_DOWN"_T.data(),
		    "VIEW_VEHICLE_CONTROL_RAISING"_T.data(),
		};

		if (g_vehicle_control_service.m_controlled_vehicle.is_convertible)
		{
			components::button(g_vehicle_control_service.m_controlled_vehicle.convertible_state ? "VIEW_VEHICLE_CONTROL_RAISE"_T : "VIEW_VEHICLE_CONTROL_LOWER"_T, [] {
				g_vehicle_control_service.vehicle_operation([] {
					if (g_vehicle_control_service.m_controlled_vehicle.convertible_state > 0)
						VEHICLE::RAISE_CONVERTIBLE_ROOF(g_vehicle_control_service.m_controlled_vehicle.handle, false);
					else
						VEHICLE::LOWER_CONVERTIBLE_ROOF(g_vehicle_control_service.m_controlled_vehicle.handle, false);
				});
			});

			ImGui::SameLine();
			ImGui::Text(std::format("{}: {}",
			    "VIEW_VEHICLE_CONTROL_CONVERTIBLE_STATE"_T,
			    convertiblestates[g_vehicle_control_service.m_controlled_vehicle.convertible_state])
			                .c_str());
		}

		if (ImGui::Checkbox(g_vehicle_control_service.m_controlled_vehicle.engine ?
		            "VIEW_DEBUG_ANIMATIONS_STOP"_T.data() :
		            "SETTINGS_NOTIFY_GTA_THREADS_START"_T.data(),
		        &g_vehicle_control_service.m_controlled_vehicle.engine))
		{
			g_fiber_pool->queue_job([=] {
				g_vehicle_control_service.vehicle_operation([] {
					VEHICLE::SET_VEHICLE_ENGINE_ON(g_vehicle_control_service.m_controlled_vehicle.handle,
					    !g_vehicle_control_service.m_controlled_vehicle.engine,
					    true,
					    false);
				});
			});
		}

		ImGui::SameLine();
		ImGui::Text(
		    std::format("{}: {}", "VIEW_VEHICLE_CONTROL_ENGINE"_T, g_vehicle_control_service.m_controlled_vehicle.engine ? "VIEW_VEHICLE_CONTROL_ENGINE_RUNNING"_T : "OFF"_T)
		        .c_str());

		components::button(g_vehicle_control_service.m_driver_performing_task ? "CANCEL"_T : "VIEW_VEHICLE_CONTROL_SUMMON"_T, [] {
			if (!g_vehicle_control_service.m_driver_performing_task)
				g_vehicle_control_service.vehicle_operation([] {
					g_vehicle_control_service.summon_vehicle();
				});
			else
				g_vehicle_control_service.m_driver_performing_task = false;
		});

		if (g_vehicle_control_service.m_driver_performing_task)
		{
			ImGui::SameLine();
			ImGui::Text(std::format("{}: {}", "VIEW_SELF_CUSTOM_TELEPORT_DISTANCE"_T, g_vehicle_control_service.m_distance_to_destination)
			                .c_str());


			ImGui::Text(std::format("{}: {}", "OUTFIT_TASK"_T, g_vehicle_control_service.m_currentask).c_str());
		}
	}

	bool_command use_animations("vehcontroluseanims", "VIEW_VEHICLE_CONTROL_USE_ANIMATIONS", "VIEW_VEHICLE_CONTROL_USE_ANIMATIONS_DESC",
	    g.window.vehicle_control.operation_animation);
	bool_command render_veh_dist("vehcontrolrendervehdist", "VIEW_VEHICLE_CONTROL_RENDER_DISTANCE_ON_VEHICLE", "VIEW_VEHICLE_CONTROL_RENDER_DISTANCE_ON_VEHICLE_DESC",
	    g.window.vehicle_control.render_distance_on_veh);
	bool_command show_vehicle_info("vehcontrolshowvehinfo", "VIEW_VEHICLE_CONTROL_SHOW_VEHICLE_INFO", "VIEW_VEHICLE_CONTROL_SHOW_VEHICLE_INFO_DESC",
	    g.window.vehicle_control.show_info);

	void render_settings_tab()
	{
		components::command_checkbox<"vehcontroluseanims">();
		components::command_checkbox<"vehcontrolrendervehdist">();
		components::command_checkbox<"vehcontrolshowvehinfo">();

		ImGui::SeparatorText("VIEW_VEHICLE_CONTROL_SELECTION_MODE"_T.data());
		ImGui::RadioButton("VIEW_VEHICLE_CONTROL_SELECTION_MODE_LAST_DRIVEN"_T.data(), (int*)&g_vehicle_control_service.m_selection_mode, (int)eControlledVehSelectionMode::LAST_DRIVEN);
		ImGui::SameLine();
		ImGui::RadioButton("VIEW_VEHICLE_CONTROL_SELECTION_MODE_PERSONAL_VEHICLE"_T.data(),
		    (int*)&g_vehicle_control_service.m_selection_mode,
		    (int)eControlledVehSelectionMode::PERSONAL);
		ImGui::SameLine();
		ImGui::RadioButton("VIEW_VEHICLE_CONTROL_SELECTION_MODE_CLOSEST"_T.data(), (int*)&g_vehicle_control_service.m_selection_mode, (int)eControlledVehSelectionMode::CLOSEST);
	}

	void view::vehicle_control()
	{
		if (!g.window.vehicle_control.opened)
			return;

		ImGui::SetNextWindowPos(ImVec2(500.0f, 10.0f), ImGuiCond_FirstUseEver, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.5f);
		if (ImGui::Begin("VEHICLE_CONTROLLER"_T.data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			if (g_vehicle_control_service.m_controlled_vehicle_exists)
			{
				ImGui::Text(g_vehicle_control_service.m_controlled_vehicle.model_name);
				if (g.window.vehicle_control.show_info)
				{
					ImGui::Text(std::vformat("VIEW_VEHICLE_CONTROL_HEALTH_N_PASSENGERS"_T,
					    std::make_format_args(g_vehicle_control_service.m_controlled_vehicle.ptr->m_health,
					        g_vehicle_control_service.m_controlled_vehicle.ptr->m_num_of_passengers,
					        g_vehicle_control_service.m_controlled_vehicle.ptr->m_max_passengers))
					                .c_str());
				}

				ImGui::Separator();
				ImGui::Spacing();
				if (ImGui::BeginTabBar("##vehiclecontroltabbar"))
				{
					if (ImGui::BeginTabItem("VIEW_VEHICLE_CONTROL_DOORS"_T.data()))
					{
						render_doors_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("VIEW_VEHICLE_CONTROL_WINDOWS"_T.data()))
					{
						render_windows_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("VEHICLE_CONTROLLER_NEON_LIGHTS"_T.data()))
					{
						render_lights_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("FUN_VEHICLE_SEAT"_T.data()))
					{
						render_seats_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("SETTINGS_MISC"_T.data()))
					{
						render_misc_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("GUI_TAB_SETTINGS"_T.data()))
					{
						render_settings_tab();

						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			}
			else
			{
				ImGui::Text("PLAYER_INFO_NO_VEHICLE"_T.data());
			}
		}
		ImGui::End();
	}
}