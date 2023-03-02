#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class aimbot : looped_command
	{
		using looped_command::looped_command;

		Vector3 aim_lock;
		Vector2 mouse_movement;

		virtual void on_tick() override
		{
			float local_fov_change = g.weapons.aimbot.fov;
			for (auto ped : entity::get_entities(false, true))
			{
				if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, ped, 17) && !ENTITY::IS_ENTITY_DEAD(ped, 0))// Tracetype is always 17. LOS check
				{
					int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self::ped);// relation for enemy check
					int type     = PED::GET_PED_TYPE(ped);// for police check, cop types are 6, swat is 27
					Vector3 world_position = ENTITY::GET_ENTITY_COORDS(ped, false);

					if (SYSTEM::VDIST(self::pos.x,
					        self::pos.y,
					        self::pos.z,
					        world_position.x,
					        world_position.y,
					        world_position.z)
					    > g.weapons.aimbot.distance)
						continue;// If the entity is further than our preset distance then just skip it

					if (PED::IS_PED_A_PLAYER(ped) && g.weapons.aimbot.on_player)// check if its a player
					{
						goto aimbot_handler;
					}
					else if (((relation == 4) || (relation == 5)) && g.weapons.aimbot.on_enemy)// relation 4 and 5 are for enemies
					{
						goto aimbot_handler;
					}
					else if (((type == 6 && !PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_uscg_01"))) || type == 27 ||// s_m_y_uscg_01 = us coast guard 1 (techniaclly military)
					             PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_ranger_01")) || PED::IS_PED_MODEL(ped, rage::joaat("s_f_y_ranger_01")))// ranger models
					    && g.weapons.aimbot.on_police)
					{
						goto aimbot_handler;
					}
					else if (g.weapons.aimbot.on_npc && !PED::IS_PED_A_PLAYER(ped))

					// Update aim lock coords
					aimbot_handler:
					{// Jump to here to handle instead of continue statements
						aim_lock =
						    ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, g.weapons.aimbot.selected_bone));
						if ((aim_lock.x != 0) && (aim_lock.y != 0) && (aim_lock.z != 0))// Ensure none of the coords are = to 0
						{
							Vector2 screen_dim, movement;
							GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(aim_lock.x,
							    aim_lock.y,
							    aim_lock.z,
							    &screen_dim.x,
							    &screen_dim.y);
							if ((screen_dim.x >= 0) && (screen_dim.y >= 0))// Make sure updated screen dim is greater than 0
							{
								auto& io = ImGui::GetIO();
								ImVec2 center(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f);// Use ImGui to get the display size
								//Screen dim is a float between 0-1, multiply the float by screen coords
								screen_dim.x *= io.DisplaySize.x;
								screen_dim.y *= io.DisplaySize.y;

								if (screen_dim.x > center.x)//If the location is greater than the center (right side)
								{// Get the amount of distance we need to move, so center of the screen - our location
									movement.x = -(center.x - screen_dim.x);
									if (movement.x + center.x > center.x * 2)
										movement.x = 0;
								}
								else
								{// if the location is on the left side
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
								{// sqrt of movment x and y ^ 2, handles fov math
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
					update_time_now = false;//lockout
				}

				std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - current_time;
				if (elapsed_time.count() > 0.f)
				{
					INPUT mouse_handle;// MOUSEINPUT mi;
					mouse_handle.type = INPUT_MOUSE;
					mouse_handle.mi.dwFlags = MOUSEEVENTF_MOVE;// Type = Mouse movement, and the event  is emulating the mouse movement

					// Update the mouse by moving it with how much we need / smoothing speed
					mouse_handle.mi.dx = mouse_movement.x / (g.weapons.aimbot.smoothing ? g.weapons.aimbot.smoothing_speed : 2);
					mouse_handle.mi.dy = mouse_movement.y / (g.weapons.aimbot.smoothing ? g.weapons.aimbot.smoothing_speed : 2);
					SendInput(1, &mouse_handle, sizeof(mouse_handle));//handles the input

					//Reset our variables
					mouse_movement.x = 0, mouse_movement.y = 0;
					update_time_now = true;//reset our time
				}
			}
		}
	};

	aimbot g_aimbot("aimbot", "Aimbot", "lock on and kill", g.weapons.aimbot.enable);
	bool_command g_smoothing("smoothing", "Smoothing", "Controls the snappiness of your lock on", g.weapons.aimbot.smoothing);
	bool_command g_aimbot_on_player("aimatplayer", "Player", "If you suck at pvp this is for you.", g.weapons.aimbot.on_player);
	bool_command g_aimbot_on_npc("aimatnpc", "NPC", "Generally kills normal NPCs", g.weapons.aimbot.on_npc);
	bool_command g_aimbot_on_police("aimatpolice", "Police", "Locks onto cops to kill", g.weapons.aimbot.on_police);
	bool_command
	    g_aimbot_on_enemy("aimatenemy", "Enemy", "Eliminate your enemies, and win your missions", g.weapons.aimbot.on_enemy);
}
