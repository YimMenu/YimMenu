#include "backend/bool_command.hpp"
#include "backend/float_command.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class super_hero_fly : looped_command
	{
		using looped_command::looped_command;

		bool m_flying            = false;
		bool m_landing           = false;
		bool m_launching         = false;
		bool m_anims_are_playing = false;

		bool m_timer = false;
		std::chrono::system_clock::time_point m_time_stamp;
		std::chrono::duration<double> m_duration;

		bool m_charging             = false;
		double m_charge_intensity   = 1;
		int m_charge_ptfx           = 0;
		float m_explosion_intensity = 0;

		Vehicle m_veh_handle{};
		Vector3 m_land_coords{};
		Vector3 m_fly_motion{};

		void reset()
		{
			m_flying              = false;
			m_landing             = false;
			m_launching           = false;
			m_timer               = false;
			m_charging            = false;
			m_charge_intensity    = 0;
			m_charge_ptfx         = 0;
			m_explosion_intensity = 0;
			TASK::CLEAR_PED_TASKS(self::ped);
			m_time_stamp = std::chrono::system_clock::now();
			PED::SET_PED_CAN_RAGDOLL(self::ped, true);
			detach_delete_vehicle();
			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry1"))
				STREAMING::REMOVE_NAMED_PTFX_ASSET("scr_rcbarry1");
		}

		void apply_fly_animations(bool apply_lower_body, bool apply_uppder_body)
		{
			//A mix of two animations with their flags specifically tailored to mimic a sort of superman stance

			if (apply_lower_body)
				ped::ped_play_animation(self::ped, "skydive@parachute@first_person", "chute_idle_alt_lookright", 4, 1, -1, 1 | 1048576);

			if (apply_uppder_body)
				ped::ped_play_animation(self::ped, "missfam5_yoga", "c8_to_start", 4, 1, -1, 2 | 16 | 32 | 131072 | 1048576);
		}

		void apply_explosion()
		{
			if (g.self.super_hero_fly.explosions)
				FIRE::ADD_EXPLOSION(self::pos.x, self::pos.y, self::pos.z, eExplosionTag::TANKSHELL, 0, true, true, 1, true);
		}

		void detach_delete_vehicle()
		{
			ENTITY::DETACH_ENTITY(m_veh_handle, false, false);
			ENTITY::DETACH_ENTITY(self::ped, true, true);
			ENTITY::SET_ENTITY_COLLISION(m_veh_handle, false, false);
			script::get_current()->yield(50ms);

			if (ENTITY::DOES_ENTITY_EXIST(m_veh_handle))
			{
				if (entity::take_control_of(m_veh_handle))
				{
					ENTITY::DETACH_ENTITY(m_veh_handle, false, false);

					entity::delete_entity(m_veh_handle);
				}
			}
		}

		void create_psuedo_vehicle()
		{
			detach_delete_vehicle();
			m_veh_handle = vehicle::spawn(0xEEF345EC, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.0, 0.0, 5.f), ENTITY::GET_ENTITY_HEADING(self::ped), true, false);
			VEHICLE::SET_VEHICLE_GRAVITY(m_veh_handle, false);
			ENTITY::SET_ENTITY_INVINCIBLE(m_veh_handle, true);
			ENTITY::SET_ENTITY_VISIBLE(m_veh_handle, false, 0);
		}

		void attach_to_psuedo_vehicle()
		{
			if (ENTITY::DOES_ENTITY_EXIST(m_veh_handle))
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(self::ped, m_veh_handle, 0, 0, 0, 0, 0, 0, 0, true, false, false, false, 0, true, false);
			}
		}

		void gravitate(Entity ent, Vector3 coord, float speed)
		{
			ENTITY::SET_ENTITY_VELOCITY(ent,
			    (coord.x - self::pos.x) * speed,
			    (coord.y - self::pos.y) * speed,
			    (coord.z - self::pos.z) * speed);
		}

		/*
		This method is called in conjunction with a pressed key, so it can be considered a loop.
		Consider all its content to have a lifetime similar to a while loop.
		*/
		void charge_launch()
		{
			if (ENTITY::IS_ENTITY_IN_AIR(self::ped) || ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(self::ped) > 5 || m_duration.count() < 0.2)
				return;

			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, "anim@amb@inspect@crouch@male_a@base", "base", 3))
				ped::ped_play_animation(self::ped, "anim@amb@inspect@crouch@male_a@base", "base", 4, 1, -1, 1 | 131072 | 262144 | 1048576 | 33554432);

			m_charge_intensity = m_duration.count();

			if (m_charge_intensity > 5)
				m_charge_intensity = 5;
			if (m_explosion_intensity > 10)
				m_explosion_intensity = 10;

			if (g.self.super_hero_fly.ptfx && m_charge_intensity > 0.4)
			{
				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry1");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry1");
				m_charge_ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_alien_disintegrate",
				    self::pos.x,
				    self::pos.y,
				    self::pos.z - 1,
				    0,
				    0,
				    0,
				    m_charge_intensity / 10,
				    0,
				    0,
				    0,
				    0);

				if ((((int)(std::round(m_charge_intensity * 10)) % 5)) == 1)
				{
					for (int i = 0; i < m_explosion_intensity; i++)
					{
						FIRE::ADD_EXPLOSION(self::pos.x, self::pos.y, self::pos.z + i, eExplosionTag::EXP_TAG_TORPEDO_UNDERWATER, 0, true, true, m_charge_intensity / 10, true);
					}
					m_explosion_intensity += 0.5;
				}
			}

			m_charging = true;
		}

		/*
		Unlike the method name, this method is responsible for both initiating the flight and landing once in air.
		*/
		void launch()
		{
			if (!m_flying)
			{
				m_launching  = true;
				m_landing    = false;
				m_fly_motion = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.0, 0.0, 5.f);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);

				apply_fly_animations(true, true);

				//Avoid gravity related game mechanics to interupt any of our operations
				ENTITY::SET_ENTITY_VELOCITY(self::ped, 0, 0, 1);
				//Since flight is tightly connected to the animations, flying is only true if and when the animations are playing.
				m_flying = true;

				create_psuedo_vehicle();
				attach_to_psuedo_vehicle();

				//Special effect if player is on ground
				if (!ENTITY::IS_ENTITY_IN_AIR(m_veh_handle) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(m_veh_handle) < 10)
				{
					m_fly_motion = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped,
					    0.0,
					    0.0,
					    g.self.super_hero_fly.charge ? m_charge_intensity * 50 : g.self.super_hero_fly.initial_launch);

					apply_explosion();
				}

				m_charge_intensity = 0;
				m_timer            = false;
				GRAPHICS::STOP_PARTICLE_FX_LOOPED(m_charge_ptfx, false);
				STREAMING::REMOVE_NAMED_PTFX_ASSET("scr_rcbarry1");
				m_charge_ptfx         = 0;
				m_explosion_intensity = 0;
				m_launching           = false;

				//Relying on a script yield, we return since flying wasn't true. Anything beyond this point would initiate landing.
				return;
			}

			land();
		}

		void land()
		{
			if (!m_landing && m_flying)
			{
				//Negative Z velocity results in gravity assuming we are falling, hence the removal of the parachute.
				constexpr auto parachute_hash = "GADGET_PARACHUTE"_J;
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, parachute_hash);
				detach_delete_vehicle();
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
				m_flying  = false;
				m_landing = true;

				//Using raycast probe to determine where the player camera is looking at.
				m_land_coords = math::raycast_coords(CAM::GET_GAMEPLAY_CAM_COORD(), CAM::GET_GAMEPLAY_CAM_ROT(2), self::ped);

				//If the determined land_coords are further than 500, we change our landing coord to the ground beneath.
				if (math::distance_between_vectors(self::pos, m_land_coords) > 500)
				{
					m_land_coords = self::pos;
					MISC::GET_GROUND_Z_FOR_3D_COORD(self::pos.x, self::pos.y, self::pos.z, &m_land_coords.z, true, 0);
				}

				PED::SET_PED_CAN_RAGDOLL(self::ped, false);

				//Use gravitate singularly to swing the player ped to the determined land_coords. Roughly innacurate since velocity is physics based.
				gravitate(self::ped, m_land_coords, 40);
			}
		}

		virtual void on_tick() override
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, false))
			{
				if (m_flying || m_charging || m_landing || m_launching)
					reset();

				return;
			}

			//Both anims are required in order to consider the player ped flying.
			m_anims_are_playing = ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, "missfam5_yoga", "c8_to_start", 3) && ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, "skydive@parachute@first_person", "chute_idle_alt_lookright", 3);

			//Check whether animations are compromised which would mean our flight is interrupted. Reset to avoid unwanted behaviour.
			if (!m_anims_are_playing && !m_launching && m_flying)
				reset();

			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_COVER, false);

			if (m_timer)
				m_duration = std::chrono::system_clock::now() - m_time_stamp;

			//Timer is used for both the reset and the charged launch
			if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_COVER))
			{
				m_timer    = false;
				m_charging = false;

				//Check whether the button was released quickly to reset instead of initiate landing
				if (m_flying && m_duration.count() <= 0.2)
				{
					reset();
				}
				else
				{
					launch();

					script::get_current()->yield(10ms);
				}

				m_duration = std::chrono::milliseconds::zero();
			}

			//Timer is started once the button is pressed and a marker is drawn if player is flying to visualize landing coords.
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_COVER))
			{
				if (!m_timer)
				{
					m_time_stamp = std::chrono::system_clock::now();
					m_timer      = true;
				}

				if (m_flying)
				{
					auto probable_land_coords = math::raycast_coords(CAM::GET_GAMEPLAY_CAM_COORD(), CAM::GET_GAMEPLAY_CAM_ROT(2), self::ped);
					GRAPHICS::DRAW_MARKER(25, probable_land_coords.x, probable_land_coords.y, probable_land_coords.z + 0.1f, 0.f, 0.f, 0.f, 0, 0, 0, 5.f, 5.f, 5.f, 255, 255, 255, 100, 0, 0, 0, 0, 0, 0, 0);
				}
			}

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_COVER) && !m_flying
			    && g.self.super_hero_fly.charge && !PED::IS_PED_IN_ANY_VEHICLE(self::ped, false))
			{
				charge_launch();
			}

			if (m_flying)
			{
				if (g.self.super_hero_fly.fly_speed > 20)
					g.self.super_hero_fly.fly_speed = 20;
				if (g.self.super_hero_fly.fly_speed < 1)
					g.self.super_hero_fly.fly_speed = 1;

				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);

				if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(m_veh_handle))
					entity::take_control_of(m_veh_handle);

				ENTITY::SET_ENTITY_ROTATION(m_veh_handle, rot.x, rot.y, rot.z, 2, 0);

				//Gravitate is called as long as flying is true to move our player ped to the desired coords with velocity.
				gravitate(m_veh_handle, m_fly_motion, g.self.super_hero_fly.fly_speed);

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(m_veh_handle) < 1 && g.self.super_hero_fly.auto_land)
					launch();

				//Fly motion nav
				Vector3 fly_nav{};
				bool moved = false;
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				{
					fly_nav =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(m_veh_handle, 0.0, (1.0 * g.self.super_hero_fly.fly_speed), 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				{
					fly_nav = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(m_veh_handle, (-1.0 * g.self.super_hero_fly.fly_speed), 0.0, 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				{
					fly_nav = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(m_veh_handle, (1.0 * g.self.super_hero_fly.fly_speed), 0.0, 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				{
					fly_nav =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(m_veh_handle, 0.0, (-1.0 * g.self.super_hero_fly.fly_speed), 0.f);
					moved = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				{
					Vector3 above = {self::pos.x, self::pos.y, self::pos.z + (float)(1.0 * g.self.super_hero_fly.fly_speed)};
					fly_nav = above;
					moved   = true;
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				{
					Vector3 below = {self::pos.x, self::pos.y, self::pos.z - (float)(1.0 * g.self.super_hero_fly.fly_speed)};
					fly_nav = below;
					moved   = true;
				}

				if (moved)
				{
					//Gradual smoothes the flight by incrementing speed as long as we are moving
					if (g.self.super_hero_fly.gradual)
					{
						g.self.super_hero_fly.fly_speed += 0.1f;
					}
					m_fly_motion = fly_nav;
					moved      = false;
				}
				else
				{
					//Reset the speed for gradual movement
					if (g.self.super_hero_fly.gradual)
					{
						g.self.super_hero_fly.fly_speed = 1.f;
					}
				}
			}

			if (m_landing)
			{
				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(self::ped) < 2 || !ENTITY::IS_ENTITY_IN_AIR(self::ped))
				{
					detach_delete_vehicle();

					ENTITY::SET_ENTITY_VELOCITY(self::ped, 0, 0, 0);
					TASK::CLEAR_PED_TASKS(self::ped);
					m_landing = false;
					ENTITY::SET_ENTITY_VELOCITY(m_veh_handle, 0, 0, 0);
					ped::ped_play_animation(self::ped, "move_fall@beastjump", "high_land_stand", 4, -4, 2000, 0 | 4);
					apply_explosion();
					reset();
				}
			}
		}

		virtual void on_enable() override
		{
			g_notification_service.push("SUPER_HERO_FLY"_T.data(), "SUPER_HERO_FLY_ENABLE_NOTIFICATION"_T.data());
		}

		virtual void on_disable() override
		{
			reset();
		}
	};

	super_hero_fly g_super_hero_fly("superherofly", "SUPER_HERO_FLY", "SUPER_HERO_FLY_DESC", g.self.super_hero_fly.enabled);
	bool_command gradual_speed("superheroflygradualspeed", "SUPER_HERO_FLY_GRADUAL_SPEED", "SUPER_HERO_FLY_GRADUAL_SPEED_DESC",
	    g.self.super_hero_fly.gradual);
	bool_command explosions("superheroflyexplosions", "SUPER_HERO_FLY_EXPLOSIONS", "SUPER_HERO_FLY_EXPLOSIONS_DESC",
	    g.self.super_hero_fly.explosions);
	bool_command auto_land("superheroflyautoland", "SUPER_HERO_FLY_AUTO_LAND", "SUPER_HERO_FLY_AUTO_LAND_DESC",
	    g.self.super_hero_fly.auto_land);
	bool_command charge_launch("superheroflychargelaunch", "SUPER_HERO_FLY_CHARGE_LAUNCH", "SUPER_HERO_FLY_CHARGE_LAUNCH_DESC",
	    g.self.super_hero_fly.charge);
	bool_command charge_ptfx("superheroflychargeptfx", "SUPER_HERO_FLY_CHARGE_PTFX", "SUPER_HERO_FLY_CHARGE_PTFX_DESC",
	    g.self.super_hero_fly.ptfx);
	float_command speed("superheroflyspeed", "SUPER_HERO_FLY_SPEED", "SUPER_HERO_FLY_SPEED_DESC", g.self.super_hero_fly.fly_speed, 1.f, 50.f);
	float_command initial_launch("superheroflyinitiallaunch", "SUPER_HERO_FLY_INITIAL_LAUNCH", "SUPER_HERO_FLY_INITIAL_LAUNCH_DESC",
	    g.self.super_hero_fly.initial_launch, 1.f, 50.f);
}
