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

		virtual void on_tick() override
		{
			float local_fov_change = g.weapons.aimbot.fov;
			for (auto ped : entity::get_entities(false, true))
			{
				if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) // Tracetype is always 17. LOS check
				{
					int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self::ped); // relation for enemy check
					int type     = PED::GET_PED_TYPE(ped); // for police check, cop types are 6, swat is 27
					Vector3 world_position = ENTITY::GET_ENTITY_COORDS(ped, false);

					if (SYSTEM::VDIST2(self::pos.x,
					        self::pos.y,
					        self::pos.z,
					        world_position.x,
					        world_position.y,
					        world_position.z)
					    > (g.weapons.aimbot.distance * g.weapons.aimbot.distance))
						continue; // If the entity is further than our preset distance then just skip it

					if (PED::IS_PED_A_PLAYER(ped) && g.weapons.aimbot.on_player) // check if its a player
					{
						goto aimbot_handler;
					}
					else if (((relation == 4) || (relation == 5)) && g.weapons.aimbot.on_enemy) // relation 4 and 5 are for enemies
					{
						goto aimbot_handler;
					}
					else if (((type == 6 && !PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_uscg_01"))) || type == 27 || // s_m_y_uscg_01 = us coast guard 1 (technically military)
					             PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_ranger_01")) || PED::IS_PED_MODEL(ped, rage::joaat("s_f_y_ranger_01"))) // ranger models
					    && g.weapons.aimbot.on_police)
					{
						goto aimbot_handler;
					}
					else if (g.weapons.aimbot.on_npc && !PED::IS_PED_A_PLAYER(ped))

					// Update aim lock coords
					aimbot_handler:
					{
						if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, ped, 17))
							continue;

						// Jump to here to handle instead of continue statements
						aim_lock =
						    ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, g.weapons.aimbot.selected_bone));
					}
				}
			}

			if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_AIM))
			{
				Vector3 camera_target = aim_lock - CAM::GET_GAMEPLAY_CAM_COORD();
				float camera_heading  = atan2f(camera_target.x, camera_target.y) * 180.0 / 3.14159265358979323846;
				float magnitude       = sqrtf(camera_target.x * camera_target.x + camera_target.y * camera_target.y
                    + camera_target.z * camera_target.z);

				float camera_pitch = asinf(camera_target.z / magnitude) * 180.0 / 3.14159265358979323846;
				float self_heading = ENTITY::GET_ENTITY_HEADING(self::ped);
				float self_pitch   = ENTITY::GET_ENTITY_PITCH(self::ped);
				if (camera_heading >= 0.0 && camera_heading <= 180.0)
				{
					camera_heading = 360.0 - camera_heading;
				}
				else if (camera_heading <= -0.0 && camera_heading >= -180.0)
				{
					camera_heading = -camera_heading;
				}
				if (CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == 4)
				{
					CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(camera_heading - self_heading);
					CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(camera_pitch - self_pitch);
				}
				else
				{
					CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(camera_heading - self_heading);
					CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(camera_pitch - self_pitch, 1065353216);
				}
			}
		}
	};

	aimbot g_aimbot("aimbot", "VIEW_OVERLAY_AIMBOT", "BACKEND_LOOPED_WEAPONS_AIMBOT_DESC", g.weapons.aimbot.enable);
	bool_command
	    g_aimbot_on_player("aimatplayer", "PLAYER", "BACKEND_LOOPED_WEAPONS_AIM_AT_PLAYER_DESC", g.weapons.aimbot.on_player);
	bool_command g_aimbot_on_npc("aimatnpc", "NPC", "BACKEND_LOOPED_WEAPONS_AIM_AT_NPC_DESC", g.weapons.aimbot.on_npc);
	bool_command
	    g_aimbot_on_police("aimatpolice", "POLICE", "BACKEND_LOOPED_WEAPONS_AIM_AT_POLICE_DESC", g.weapons.aimbot.on_police);
	bool_command g_aimbot_on_enemy("aimatenemy", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY_DESC",
	    g.weapons.aimbot.on_enemy);
}
