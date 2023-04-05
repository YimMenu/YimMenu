#include "gta_util.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "services/vehicle/vehicle_control_service.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{

	void render_doors_tab()
	{
		const char* const doornames[MAX_VEHICLE_DOORS]{
		    "Front left",
		    "Front right",
		    "Back left",
		    "Back right",
		    "Bonnet",
		    "Trunk",
		};

		const char* const locknames[MAX_VEHICLE_LOCK_STATES]{
		    "None",
		    "Unlocked",
		    "Locked",
		    "Lockout player only",
		    "Locked player inside",
		    "Locked initially",
		    "Force shut doors",
		    "Locked but damageable",
		    "Locked but boot unlocked",
		    "Locked no passengers",
		    "Cannot enter",
		};

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("##alldoorslock", "All doors"))
		{
			for (int lockindex = 0; lockindex < MAX_VEHICLE_LOCK_STATES; lockindex++)
			{
				if (ImGui::Selectable(locknames[lockindex]))
				{
					g_fiber_pool->queue_job([=] {
						vehicle::change_vehicle_door_lock_state(g_vehicle_control_service.m_controlled_vehicle.handle, eDoorId::VEH_EXT_DOOR_INVALID_ID, (eVehicleLockState)lockindex);
					});
				};
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();

		if (ImGui::Button("Open all"))
		{
			g_fiber_pool->queue_job([=] {
				g_vehicle_control_service.operate_door(eDoorId::VEH_EXT_DOOR_INVALID_ID, true);
			});
		}
		ImGui::SameLine();

		if (ImGui::Button("Close all"))
		{
			g_fiber_pool->queue_job([=] {
				g_vehicle_control_service.operate_door(eDoorId::VEH_EXT_DOOR_INVALID_ID, false);
			});
		}

		ImGui::EndGroup();

		ImGui::Separator();

		ImGui::BeginGroup();

		for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
		{
			if (!g_vehicle_control_service.m_controlled_vehicle.doors[i].valid)
				continue;
			ImGui::SetNextItemWidth(200);
			if (ImGui::BeginCombo(doornames[i], locknames[(int)g_vehicle_control_service.m_controlled_vehicle.doors[i].lockstate]))
			{
				for (int lockindex = 0; lockindex < MAX_VEHICLE_LOCK_STATES; lockindex++)
				{
					if (ImGui::Selectable(locknames[lockindex]))
					{
						g_fiber_pool->queue_job([=] {
							vehicle::change_vehicle_door_lock_state(g_vehicle_control_service.m_controlled_vehicle.handle, (eDoorId)i, (eVehicleLockState)lockindex);
						});
					};
				}
				ImGui::EndCombo();
			}

			ImGui::SameLine(300);

			std::string buttonlabel = g_vehicle_control_service.m_controlled_vehicle.doors[i].open ? "Close" : "Open";
			buttonlabel.append("##").append(std::to_string(i));
			if (ImGui::Button(buttonlabel.data()))
			{
				g_fiber_pool->queue_job([=] {
					g_vehicle_control_service.operate_door((eDoorId)i,
					    !g_vehicle_control_service.m_controlled_vehicle.doors[i].open);
				});
			}
		}


		ImGui::EndGroup();
	}

	void render_lights_tab()
	{
		const char* const neonnames[4]{
		    "Left",
		    "Right",
		    "Front",
		    "Rear",
		};

		if (ImGui::Button("Toggle lights"))
		{
			g_fiber_pool->queue_job([=] {
				g_vehicle_control_service.operate_lights(!g_vehicle_control_service.m_controlled_vehicle.headlights, false);
			});
		}
		ImGui::SameLine();
		if (ImGui::Button("Toggle High beams"))
		{
			g_fiber_pool->queue_job([=] {
				g_vehicle_control_service.operate_lights(g_vehicle_control_service.m_controlled_vehicle.headlights,
				    !g_vehicle_control_service.m_controlled_vehicle.highbeams);
			});
		}
		if (ImGui::Button("Interior lights on"))
		{
			g_fiber_pool->queue_job([=] {
				if (g.window.vehicle_control.operation_animation)
					g_vehicle_control_service.animated_vehicle_operation(self::ped);
				VEHICLE::SET_VEHICLE_INTERIORLIGHT(g_vehicle_control_service.m_controlled_vehicle.handle, true);
			});
		}
		ImGui::SameLine();
		if (ImGui::Button("Interior lights off"))
		{
			g_fiber_pool->queue_job([=] {
				if (g.window.vehicle_control.operation_animation)
					g_vehicle_control_service.animated_vehicle_operation(self::ped);
				VEHICLE::SET_VEHICLE_INTERIORLIGHT(g_vehicle_control_service.m_controlled_vehicle.handle, false);
			});
		}

		ImGui::Text("Neon lights");
		ImGui::Separator();

		for (int i = 0; i < 4; i++)
		{
			if (ImGui::Checkbox(neonnames[i], &g_vehicle_control_service.m_controlled_vehicle.neons[i]))
			{
				g_fiber_pool->queue_job([=] {
					g_vehicle_control_service.operate_neons(i, g_vehicle_control_service.m_controlled_vehicle.neons[i]);
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
		    "Driver",
		    "Passenger",
		    "Left rear",
		    "Right rear",
		    "Outside Left",
		    "Outside Right",
		};

		static int movespeed = 1;

		if (ImGui::RadioButton("Walk", movespeed == 1))
			movespeed = 1;
		ImGui::SameLine();
		if (ImGui::RadioButton("Run", movespeed == 2))
			movespeed = 2;
		ImGui::SameLine();
		if (ImGui::RadioButton("Sprint", movespeed == 3))
			movespeed = 3;

		for (int i = 0; i < 6; i++)
		{
			if (ImGui::Button(seatnames[i]))
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
		    "Up",
		    "Lowering",
		    "Down",
		    "Raising",
		};

		if (g_vehicle_control_service.m_controlled_vehicle.isconvertible)
		{
			if (ImGui::Button(g_vehicle_control_service.m_controlled_vehicle.convertibelstate ? "Raise" : "Lower"))
			{
				g_fiber_pool->queue_job([=] {
					if (g.window.vehicle_control.operation_animation)
						g_vehicle_control_service.animated_vehicle_operation(self::ped);

					if (g_vehicle_control_service.m_controlled_vehicle.convertibelstate > 0)
						VEHICLE::RAISE_CONVERTIBLE_ROOF(g_vehicle_control_service.m_controlled_vehicle.handle, false);
					else
						VEHICLE::LOWER_CONVERTIBLE_ROOF(g_vehicle_control_service.m_controlled_vehicle.handle, false);
				});
			}

			ImGui::SameLine();
			ImGui::Text("Convertible state: %s", convertiblestates[g_vehicle_control_service.m_controlled_vehicle.convertibelstate]);
		}

		if (ImGui::Checkbox(g_vehicle_control_service.m_controlled_vehicle.engine ? "Stop" : "Start",
		        &g_vehicle_control_service.m_controlled_vehicle.engine))
		{
			g_fiber_pool->queue_job([=] {
				if (g.window.vehicle_control.operation_animation)
					g_vehicle_control_service.animated_vehicle_operation(self::ped);

				if (entity::take_control_of(g_vehicle_control_service.m_controlled_vehicle.handle))
					VEHICLE::SET_VEHICLE_ENGINE_ON(g_vehicle_control_service.m_controlled_vehicle.handle,
					    !g_vehicle_control_service.m_controlled_vehicle.engine,
					    true,
					    false);
			});
		}

		ImGui::SameLine();
		ImGui::Text("Engine: %s", g_vehicle_control_service.m_controlled_vehicle.engine ? "Running" : "Off");

		components::button(g_vehicle_control_service.m_driver_performing_task ? "Cancel" : "Summon", [] {
			if (!g_vehicle_control_service.m_driver_performing_task)
			{
				if (g.window.vehicle_control.operation_animation)
					g_vehicle_control_service.animated_vehicle_operation(self::ped);

				g_vehicle_control_service.summon_vehicle();
			}
			else
				g_vehicle_control_service.m_driver_performing_task = false;
		});

		if (g_vehicle_control_service.m_driver_performing_task)
		{
			ImGui::SameLine();
			ImGui::Text("Distance: %d", g_vehicle_control_service.m_distance_to_destination);


			ImGui::Text("Task: %s", g_vehicle_control_service.m_currentask);
		}
	}

	void render_settings_tab()
	{
		ImGui::Checkbox("Use animations", &g.window.vehicle_control.operation_animation);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Will use animations for several vehicle operations such as:\ntoggling lights, opening/closing doors and entering seats");
			ImGui::EndTooltip();
		}

		ImGui::Checkbox("Render distance on vehicle", &g.window.vehicle_control.render_distance_on_veh);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Will display the distance on the controlled vehicle");
			ImGui::EndTooltip();
		}

		ImGui::SliderFloat("Max summon distance", &g.window.vehicle_control.max_summon_range, 10.f, 250.f);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("At what range the vehicle will drive towards the summoned location as oposed to being teleported");
			ImGui::EndTooltip();
		}
	}

	void view::vehicle_control()
	{
		if (!g.window.vehicle_control.opened || !*g_pointers->m_is_session_started)
			return;

		ImGui::SetNextWindowPos(ImVec2(500.0f, 10.0f), ImGuiCond_FirstUseEver, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.5f);
		if (ImGui::Begin("Vehicle controller", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			if (g_vehicle_control_service.m_controlled_vehicle_exists)
			{
				ImGui::Text(g_vehicle_control_service.m_controlled_vehicle.model_name);
				ImGui::Separator();
				ImGui::Spacing();
				if (ImGui::BeginTabBar("##vehiclecontroltabbar"))
				{
					if (ImGui::BeginTabItem("Doors"))
					{
						render_doors_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Lights"))
					{
						render_lights_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Seats"))
					{
						render_seats_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Misc"))
					{
						render_misc_tab();

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Settings"))
					{
						render_settings_tab();

						ImGui::EndTabItem();
					}


					ImGui::EndTabBar();
				}
			}
			else
			{
				ImGui::Text("No vehicle available");
			}
		}
		ImGui::End();
	}
}