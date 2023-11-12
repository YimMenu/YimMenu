#include "backend/looped_command.hpp"
#include "core/data/weapons.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

#include <imgui.h>

constexpr float smoothing_speed = 4.f;
constexpr float fov             = 90.f;

namespace big
{
	class aimbot : looped_command
	{
		using looped_command::looped_command;

		Vector3 aim_lock;
		Vector2 mouse_movement;

		virtual void on_tick() override
		{
			float local_fov_change = fov;
			for (auto ped : entity::get_entities(false, true))
			{
				if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) // Tracetype is always 17. LOS check
				{
					int type               = PED::GET_PED_TYPE(ped); // for police check, cop types are 6, swat is 27
					Vector3 world_position = ENTITY::GET_ENTITY_COORDS(ped, false);

					if (SYSTEM::VDIST2(self::pos.x,
					        self::pos.y,
					        self::pos.z,
					        world_position.x,
					        world_position.y,
					        world_position.z)
					    > (g_weapons.aimbot.distance * g_weapons.aimbot.distance))
						continue; // If the entity is further than our preset distance then just skip it

					if (PED::IS_PED_A_PLAYER(ped)) // check if its a player
					{
						if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, ped, 17))
							continue;

						// Jump to here to handle instead of continue statements
						aim_lock = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, 0x796E));
						if ((aim_lock.x != 0) && (aim_lock.y != 0) && (aim_lock.z != 0)) // Ensure none of the coords are = to 0
						{
							Vector2 screen_dim, movement;
							GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(aim_lock.x,
							    aim_lock.y,
							    aim_lock.z,
							    &screen_dim.x,
							    &screen_dim.y);
							if ((screen_dim.x >= 0) && (screen_dim.y >= 0)) // Make sure updated screen dim is greater than 0
							{
								auto& io = ImGui::GetIO();
								ImVec2 center(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f); // Use ImGui to get the display size
								//Screen dim is a float between 0-1, multiply the float by screen coords
								screen_dim.x *= io.DisplaySize.x;
								screen_dim.y *= io.DisplaySize.y;

								if (screen_dim.x > center.x) //If the location is greater than the center (right side)
								{ // Get the amount of distance we need to move, so center of the screen - our location
									movement.x = -(center.x - screen_dim.x);
									if (movement.x + center.x > center.x * 2)
										movement.x = 0;
								}
								else
								{ // if the location is on the left side
									movement.x = screen_dim.x - center.x;
									if (movement.x + center.x < 0)
										movement.x = 0;
								}

								// Same thing here but for y, so switch right with up and left with down
								if (screen_dim.y > center.y)
								{
									movement.y = -(center.y - screen_dim.y);
									if (movement.y + center.y > center.y * 2)
										movement.x = 0;
								}
								else
								{
									movement.y = screen_dim.y - center.y;
									if (movement.y + center.y < 0)
										movement.y = 0;
								}

								if (sqrt(pow(movement.x, 2) + pow(movement.y, 2)) < local_fov_change)
								{ // sqrt of movment x and y ^ 2, handles fov math
									local_fov_change = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
									mouse_movement.x = movement.x;
									mouse_movement.y = movement.y;
								}
							}
						}
					}
				}
			}

			if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_AIM))
			{
				static bool update_time_now = true;
				static std::chrono::system_clock::time_point current_time;

				if (update_time_now)
				{
					current_time    = std::chrono::system_clock::now();
					update_time_now = false; //lockout
				}

				std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - current_time;
				if (elapsed_time.count() > 0.f)
				{
					INPUT mouse_handle; // MOUSEINPUT mi;
					mouse_handle.type = INPUT_MOUSE;
					mouse_handle.mi.dwFlags = MOUSEEVENTF_MOVE; // Type = Mouse movement, and the event  is emulating the mouse movement

					// Update the mouse by moving it with how much we need / smoothing speed
					mouse_handle.mi.dx = mouse_movement.x / smoothing_speed;
					mouse_handle.mi.dy = mouse_movement.y / smoothing_speed;
					SendInput(1, &mouse_handle, sizeof(mouse_handle)); //handles the input

					//Reset our variables
					mouse_movement.x = 0, mouse_movement.y = 0;
					update_time_now = true; //reset our time
				}
			}
		}
	};

	aimbot g_aimbot("aimbot", "Aimbot", "Lock on and kill", g_weapons.aimbot.enable);
}
