#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

#include <ctime>

namespace big
{
	class super_hero_fly : looped_command
	{
		using looped_command::looped_command;

		bool flying  = false;
		bool landing = false;

		bool timer = false;
		std::chrono::system_clock::time_point time_stamp;

		Vehicle veh_handle{};
		Vector3 land_coords{};
		Vector3 fly_motion{};

		void reset()
		{
			ENTITY::FREEZE_ENTITY_POSITION(veh_handle, false);
			flying  = false;
			landing = false;
			TASK::CLEAR_PED_TASKS(self::ped);
			PED::SET_RAGDOLL_BLOCKING_FLAGS(self::ped, 0);
			time_stamp = std::chrono::system_clock::now();
			detach_delete_vehicle();
		}

		void apply_fly_animations()
		{
			ped::ped_play_animation(self::ped, "skydive@parachute@first_person", "chute_idle_alt_lookright", 4, 1, -1, 1 | 131072 | 262144 | 1048576 | 33554432);
			script::get_current()->yield(100ms);
			ped::ped_play_animation(self::ped, "missfam5_yoga", "c8_to_start", 4, 1, -1, 2 | 16 | 32 | 131072 | 262144 | 1048576 | 33554432);
		}

		void apply_explosion()
		{
			if(g.self.super_hero_fly.explosions)
				FIRE::ADD_EXPLOSION(self::pos.x, self::pos.y, self::pos.z, eExplosionTag::TANKSHELL, 1, true, true, 1, true);
		}

		void detach_delete_vehicle()
		{
			ENTITY::DETACH_ENTITY(veh_handle, false, false);
			ENTITY::DETACH_ENTITY(self::ped, true, true);
			ENTITY::SET_ENTITY_COLLISION(veh_handle, false, false);
			script::get_current()->yield(50ms);

			if (ENTITY::DOES_ENTITY_EXIST(veh_handle))
			{
				if (entity::take_control_of(veh_handle))
				{
					ENTITY::DETACH_ENTITY(veh_handle, false, false);

					entity::delete_entity(veh_handle);
				}
			}
		}

		void create_psuedo_vehicle()
		{
			detach_delete_vehicle();
			veh_handle = vehicle::spawn(0xEEF345EC, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.0, 0.0, 5.f), ENTITY::GET_ENTITY_HEADING(self::ped), true, false);
			VEHICLE::SET_VEHICLE_GRAVITY(veh_handle, false);
			ENTITY::SET_ENTITY_INVINCIBLE(veh_handle, true);
			ENTITY::SET_ENTITY_VISIBLE(veh_handle, false, 0);
		}

		void attach_to_psuedo_vehicle()
		{
			auto rot = ENTITY::GET_ENTITY_ROTATION(veh_handle, 0);
			if (ENTITY::DOES_ENTITY_EXIST(veh_handle))
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(self::ped, veh_handle, 0, 0, 0, 0, 0, 0, 0, true, false, false, false, 0, true, false);
			}
		}

		void gravitate(Entity ent, Vector3 coord, float speed)
		{
			ENTITY::SET_ENTITY_VELOCITY(ent,
			    (coord.x - self::pos.x) * speed,
			    (coord.y - self::pos.y) * speed,
			    (coord.z - self::pos.z) * speed);
		}

		void launch()
		{
			if (!flying)
			{
				landing    = false;
				fly_motion = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.0, 0.0, 5.f);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
				ENTITY::SET_ENTITY_VELOCITY(self::ped, 0, 0, 0);
				apply_fly_animations();
				flying = true;

				create_psuedo_vehicle();
				attach_to_psuedo_vehicle();

				// Special effect if player is on ground
				if (!ENTITY::IS_ENTITY_IN_AIR(self::ped))
				{
					fly_motion =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.0, 0.0, g.self.super_hero_fly.initial_launch);
					apply_explosion();
					ENTITY::SET_ENTITY_VELOCITY(self::ped, 0.0, 0.0, veh_handle);
				}
				return;
			}

			land();
		}

		void land()
		{
			if (!landing && flying)
			{
				constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, parachute_hash);
				detach_delete_vehicle();
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
				flying  = false;
				landing = true;
				land_coords = math::raycast_coords(CAM::GET_GAMEPLAY_CAM_COORD(), CAM::GET_GAMEPLAY_CAM_ROT(2), self::ped);
				if (math::distance_between_vectors(self::pos, land_coords) > 500)
				{
					land_coords = self::pos;
					MISC::GET_GROUND_Z_FOR_3D_COORD(self::pos.x, self::pos.y, self::pos.z, &land_coords.z, true, 0);
				}
				gravitate(self::ped, land_coords, 40);
			}
		}

		virtual void on_tick() override
		{
			if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_COVER))
			{
				timer                                  = false;
				std::chrono::duration<double> duration = std::chrono::system_clock::now() - time_stamp;
				if (flying && duration.count() <= 0.2)
				{
					reset();
				}
				else
				{
					launch();
					script::get_current()->yield(10ms);
				}
			}

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_COVER) && flying)
			{
				if (!timer)
				{
					time_stamp = std::chrono::system_clock::now();
					timer      = true;
				}

				auto probable_land_coords = math::raycast_coords(CAM::GET_GAMEPLAY_CAM_COORD(), CAM::GET_GAMEPLAY_CAM_ROT(2), self::ped);
				GRAPHICS::DRAW_MARKER(25, probable_land_coords.x, probable_land_coords.y, probable_land_coords.z + 0.1f, 0.f, 0.f, 0.f, 0, 0, 0, 5.f, 5.f, 5.f, 255, 255, 255, 100, 0, 0, 0, 0, 0, 0, 0);
			}

			if (flying)
			{
				if(g.self.super_hero_fly.fly_speed > 20) g.self.super_hero_fly.fly_speed = 20;
				if(g.self.super_hero_fly.fly_speed < 1) g.self.super_hero_fly.fly_speed = 1;

				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION(veh_handle, rot.x, rot.y, rot.z, 2, 0);
				PED::SET_RAGDOLL_BLOCKING_FLAGS(self::ped, 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 512);
				gravitate(veh_handle, fly_motion, g.self.super_hero_fly.fly_speed);

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(veh_handle) < 1 && g.self.super_hero_fly.auto_land)
					launch();

				//Fly motion nav
				Vector3 fly_nav{};
				bool moved = false;
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				{
					fly_nav =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh_handle, 0.0, (1.0 * g.self.super_hero_fly.fly_speed), 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				{
					fly_nav = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh_handle, (-1.0 * g.self.super_hero_fly.fly_speed), 0.0, 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				{
					fly_nav = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh_handle, (1.0 * g.self.super_hero_fly.fly_speed), 0.0, 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				{
					fly_nav =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh_handle, 0.0, (-1.0 * g.self.super_hero_fly.fly_speed), 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				{
					Vector3 above = {self::pos.x, self::pos.y, self::pos.z + (float) (1.0 * g.self.super_hero_fly.fly_speed)};
					fly_nav = above;
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				{
					Vector3 below = {self::pos.x, self::pos.y, self::pos.z - (float) (1.0 * g.self.super_hero_fly.fly_speed)};
					fly_nav = below;
					moved = true;
				}

				if (moved)
				{
					if(g.self.super_hero_fly.gradual)
					{
						g.self.super_hero_fly.fly_speed += 0.1f;
					}
					fly_motion = fly_nav;
					moved      = false;
				}
				else
				{
					if (g.self.super_hero_fly.gradual)
					{
						g.self.super_hero_fly.fly_speed = 1.f;
					}
				}
			}

			if (landing)
			{
				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(self::ped) < 2 || !ENTITY::IS_ENTITY_IN_AIR(self::ped))
				{
					detach_delete_vehicle();

					ENTITY::SET_ENTITY_VELOCITY(self::ped, 0, 0, 0);
					TASK::CLEAR_PED_TASKS(self::ped);
					landing = false;
					PED::SET_RAGDOLL_BLOCKING_FLAGS(self::ped, 0);
					ENTITY::SET_ENTITY_VELOCITY(veh_handle, 0, 0, 0);
					ped::ped_play_animation(self::ped, "move_fall@beastjump", "high_land_stand", 4, -4, 2000, 0 | 4);
					apply_explosion();
				}
			}
		}

		virtual void on_enable() override
		{
			g_notification_service->push("Super hero fly", "Use the following keys to control the Super Hero Fly:\n'Q' 'SPRINT/DUCK 'WASD'.");
		}

		virtual void on_disable() override
		{
			reset();
		}
	};

	super_hero_fly g_super_hero_fly("superherofly", "Super Hero Fly", "Fly like a super hero", g.self.super_hero_fly.enabled);
}