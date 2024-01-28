#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include <numbers>
namespace big
{
	static inline Vector3 aim_lock;
	static inline Vector3 smooth_factor;
	static inline bool initalized;
	static inline Entity target_entity;

	class aimbot : looped_command
	{
		using looped_command::looped_command;
		virtual void on_tick() override
		{
			float local_fov_change = g.weapons.aimbot.fov;
			if (PED::GET_PED_CONFIG_FLAG(self::ped, 78, 0))
			{
				Entity closest_entity{};
				float distance = 1;
				for (auto ped : entity::get_entities(false, true))
				{
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(ped, 1);
					rage::fvector2 screen_pos;
					HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos.x, pos.y, pos.z, &screen_pos.x, &screen_pos.y);

					if (entity::distance_to_middle_of_screen(screen_pos) < distance && ENTITY::IS_ENTITY_ON_SCREEN(ped) && ped != self::ped)
					{
						closest_entity = ped;
						distance       = entity::distance_to_middle_of_screen(screen_pos);
					}
				}

				target_entity = closest_entity;

				int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(target_entity, self::ped);
				int type     = PED::GET_PED_TYPE(target_entity);

				if (!target_entity || ENTITY::IS_ENTITY_DEAD(target_entity, 0))
				{
					return;
				}
				Vector3 world_position = ENTITY::GET_ENTITY_COORDS(target_entity, 1);
				float distance_between_target = SYSTEM::VDIST2(self::pos.x,
				        self::pos.y,
				        self::pos.z,
				        world_position.x,
				        world_position.y,
				        world_position.z);

				if (distance_between_target > (g.weapons.aimbot.distance * g.weapons.aimbot.distance))
				{ 
					return;
				}
				if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, target_entity, 17))
				{
					return;
				}
				if (PED::IS_PED_A_PLAYER(target_entity))
				{
					if (!g.weapons.aimbot.on_player)
						return;
				}
				else if (type == ePedType::PED_TYPE_ARMY || type == ePedType::PED_TYPE_SWAT || type == ePedType::PED_TYPE_COP)
				{
					if (!g.weapons.aimbot.on_police)
						return;
					
				}
				else if (((relation == 4) || (relation == 5))) // relation 4 and 5 are for enemies
				{
					if (!g.weapons.aimbot.on_enemy)
						return;
				}
				else
				{
					if (!g.weapons.aimbot.on_npc)
						return;
				}

				aim_lock = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(target_entity,
				    PED::GET_PED_BONE_INDEX(target_entity, g.weapons.aimbot.selected_bone));

					GRAPHICS::DRAW_MARKER(3,
				    aim_lock.x,
				    aim_lock.y,
				    aim_lock.z + 0.3f,
				    0,
				    0,
				    0,
				    0,
				    180,
				    0,
				    0.3f,
				    0.3f,
				    0.3f,
				    255,255,255,255,
				    1,
				    1,
				    0,
				    0,
				    0,
				    0,
				    0);


				Vector3 camera_target;
				if (g.weapons.aimbot.smoothing)
				{
					//Avoid buggy cam
					if (!initalized)
					{
						Vector3 cam_coords      = CAM::GET_FINAL_RENDERED_CAM_COORD();
						Vector3 cam_rot         = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 cam_direction   = math::rotation_to_direction(cam_rot);
						float distance          = 150.f;
						Vector3 multiply        = cam_direction * distance;
						Vector3 front_cam       = cam_coords + multiply;
						camera_target           = front_cam - CAM::GET_FINAL_RENDERED_CAM_COORD();
						smooth_factor           = camera_target;
						initalized              = true;
					}
					Vector3 target = aim_lock - CAM::GET_FINAL_RENDERED_CAM_COORD();
					smooth_factor.x += (target.x - smooth_factor.x) * g.weapons.aimbot.smoothing_speed / 10.f;
					smooth_factor.y += (target.y - smooth_factor.y) * g.weapons.aimbot.smoothing_speed / 10.f;
					smooth_factor.z += (target.z - smooth_factor.z) * g.weapons.aimbot.smoothing_speed / 10.f;

					camera_target = smooth_factor;
				}
				else
				{
					camera_target = aim_lock - CAM::GET_FINAL_RENDERED_CAM_COORD();
				}
				//  We actually need this. For some unknow reasons it gets entity or something there.
				//  Then it will start leading to 0,0,0 coords.Aim will start pointing at 0,0,0 as well.
				if (aim_lock.x == 0.f && aim_lock.y == 0.f && aim_lock.z == 0.f)
					return;

				float RADPI          = 180.0f / std::numbers::pi;
				float camera_heading = atan2f(camera_target.x, camera_target.y) * RADPI;
				float magnitude      = sqrtf(camera_target.x * camera_target.x + camera_target.y * camera_target.y
                    + camera_target.z * camera_target.z);

				float camera_pitch = asinf(camera_target.z / magnitude) * RADPI;
				float self_heading = ENTITY::GET_ENTITY_HEADING(self::veh ? self::veh : self::ped);
				float self_pitch   = ENTITY::GET_ENTITY_PITCH(self::veh ? self::veh : self::ped);
				if (camera_heading >= 0.0f && camera_heading <= 180.0f)
				{
					camera_heading = 360.0f - camera_heading;
				}
				else if (camera_heading <= -0.0f && camera_heading >= -180.0f)
				{
					camera_heading = -camera_heading;
				}
				if (CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
				{
					CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(camera_heading - self_heading);
					CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(camera_pitch - self_pitch);
				}
				else
				{
					CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(camera_heading - self_heading);
					CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(camera_pitch - self_pitch, 1.0f);
				
				}
			}
			else
			{
				target_entity           = 0;
				initalized    = false;
			}
		}
		virtual void on_disable() override
		{
			initalized = false;
		}
	};

	aimbot g_aimbot("aimbot", "VIEW_OVERLAY_AIMBOT", "BACKEND_LOOPED_WEAPONS_AIMBOT_DESC", g.weapons.aimbot.enable);

	bool_command g_smoothing("smoothing", "BACKEND_LOOPED_WEAPONS_SMOOTHING", "BACKEND_LOOPED_WEAPONS_SMOOTHING_DESC",
	    g.weapons.aimbot.smoothing);
	bool_command
	    g_aimbot_on_player("aimatplayer", "PLAYER", "BACKEND_LOOPED_WEAPONS_AIM_AT_PLAYER_DESC", g.weapons.aimbot.on_player);
	bool_command 
		g_aimbot_on_npc("aimatnpc", "NPC", "BACKEND_LOOPED_WEAPONS_AIM_AT_NPC_DESC", g.weapons.aimbot.on_npc);
	bool_command
	    g_aimbot_on_police("aimatpolice", "POLICE", "BACKEND_LOOPED_WEAPONS_AIM_AT_POLICE_DESC", g.weapons.aimbot.on_police);
	bool_command g_aimbot_on_enemy("aimatenemy", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY_DESC",
	    g.weapons.aimbot.on_enemy);
}
