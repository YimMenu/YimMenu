#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/timer.hpp"
#include "script.hpp"
#include "util/entity.hpp"
#include "gta/enums.hpp"
#include "util/math.hpp"
#include <numbers>

namespace big
{
	static timer spawning_axe_delay(200ms);
	static timer axe_get_position_delay(300ms);

	inline int axe_particle;
	inline Entity entity_axe;
	inline Vector3 axe_flying_coords;
	inline Vector3 new_axe_flying_coords;
	inline bool axe_on_idle           = false;
	inline bool axe_attacking         = false;
	inline bool play_animation_on_ped = true;

	class flying_axe : looped_command
	{
		int get_around_position_iterator = 0;
		Vector3 get_around_position(int ent, float far_distance, float up_down_distance)
		{
			const float angleIncrement = 45.0f;
			float angle = get_around_position_iterator * angleIncrement;
			get_around_position_iterator = (get_around_position_iterator + 1) % 8;

			float angleInRadians = angle * (std::numbers::pi / 180.0f);
			float x              = far_distance * cos(angleInRadians);
			float y              = far_distance * sin(angleInRadians);

			return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, x, y, 0.0f + up_down_distance);
		}

		void play_non_loop_ptfx(int ent, const char* call1, const char* call2, const char* name, float scale, bool color, float r, float g, float b) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);

			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(call1)) {
				GRAPHICS::USE_PARTICLE_FX_ASSET(call2);
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(name, ent, 0, 0, 0, 0, 0, 0.0, scale, true, true, true);

				if (color)
					GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r / 255.f, g / 255.f, b / 255.f);
			}
		}

		void play_bone_looped_ptfx(int ent, int entbone, const char* call1, const char* call2, const char* name, float scale, bool color, float r, float g, float b) {

			if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(axe_particle)) {
				STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);

				if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(call1)) {
					GRAPHICS::USE_PARTICLE_FX_ASSET(call2);
					axe_particle = GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(name, ent, 0, 0, 0, 0, 0, 0.0, entbone, scale, true, true, true);

					if (color) {
						GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r / 255, g / 255, b / 255);
					}
				}
				STREAMING::REMOVE_PTFX_ASSET();
			}
			else {
				GRAPHICS::STOP_PARTICLE_FX_LOOPED(axe_particle, 0);
			}
		}
		void function_axe_reaction(int ent) {
			if (ent != self::veh) {
				float axe_speed  = ENTITY::GET_ENTITY_SPEED(entity_axe);
				float push_force = axe_speed * 3.5;
				if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(entity_axe, ent)) {
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) {

						Vector3 hit_impact = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(ent);

						Vector3 force = {hit_impact.x * push_force, hit_impact.y * push_force, hit_impact.z * push_force};

						ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, force.x, force.y, force.z, 0, 0, 0, false, false, true, true, false, true);

						if (ENTITY::IS_ENTITY_A_PED(ent))
							PED::APPLY_DAMAGE_TO_PED(ent, 9999, 0, 0, 2725924767);
					}
					else
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);
					}
				}
			}
		}
		float lerp(float a, float b, float t)
		{
			return a + t * (b - a);
		}
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (!ENTITY::DOES_ENTITY_EXIST(entity_axe))
			{
				// games spam axes fix
				if (spawning_axe_delay.updated())
				{
					Vector3 coordinates_to_spawn = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 0.f, 6.5f);
					Hash axe_model = rage::joaat("prop_ld_fireaxe");
					while (!STREAMING::HAS_MODEL_LOADED(axe_model))
					{
						STREAMING::REQUEST_MODEL(axe_model);
						script::get_current()->yield();
					}
					if (STREAMING::HAS_MODEL_LOADED(axe_model))

						entity_axe = OBJECT::CREATE_OBJECT(axe_model,
						    coordinates_to_spawn.x,
						    coordinates_to_spawn.y,
						    coordinates_to_spawn.z,
						    ENTITY::GET_ENTITY_HEADING(self::ped),
						    true,
						    false);

					// not sure if needed
					auto axe_net_id = NETWORK::OBJ_TO_NET(entity_axe);
					NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(entity_axe);
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(axe_net_id, true);
					//add
					Blip blip = HUD::ADD_BLIP_FOR_ENTITY(entity_axe);
					HUD::SET_BLIP_DISPLAY(blip, 8);
					HUD::SET_BLIP_SPRITE(blip, 154);
					HUD::SET_BLIP_COLOUR(blip, 38);
				}
			}
			else
			{
				float factor = 0.2f;
				axe_flying_coords.x = lerp(axe_flying_coords.x, new_axe_flying_coords.x, factor);
				axe_flying_coords.y = lerp(axe_flying_coords.y, new_axe_flying_coords.y, factor);
				axe_flying_coords.z = lerp(axe_flying_coords.z, new_axe_flying_coords.z, factor);

				auto axe_coords   = ENTITY::GET_ENTITY_COORDS(entity_axe, 0);

				if (axe_get_position_delay.updated()) {
					Vector3 rot = ENTITY::GET_ENTITY_ROTATION(entity_axe, 2);
					if (axe_on_idle) {
						new_axe_flying_coords = get_around_position(self::ped, 20.f, 0.f);
					}

					if (!axe_on_idle || axe_attacking) {
						ENTITY::SET_ENTITY_ROTATION(entity_axe, rot.x + 50.f, rot.y + 50.f, rot.z + 50.f, 2, 0);
					}
					play_bone_looped_ptfx(entity_axe, 0, "scr_powerplay", "scr_powerplay", "sp_powerplay_beast_appear_trails", 0.5f, false, 0.f, 0.f, 0.f);
					play_non_loop_ptfx(entity_axe, "scr_paletoscore", "scr_paletoscore", "scr_paleto_box_sparks", 0.1f, false, 0.f, 0.f, 0.f);
				}
				for (auto entity : entity::get_entities(true, true)) {
					function_axe_reaction(entity);
				}

				Hash wep;
				WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &wep, 1);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && !self::veh && wep == -1569615261)
				{
					Vector3 camrot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					ENTITY::SET_ENTITY_ROTATION((self::ped), camrot.x, camrot.y, camrot.z, 2, 0);
					axe_on_idle = false;
					if (!axe_attacking) {

						new_axe_flying_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, 0);

						if (SYSTEM::VDIST(self::pos.x, self::pos.y, self::pos.z, axe_coords.x, axe_coords.y, axe_coords.z) < 5) {
							if (play_animation_on_ped) {

								const char* animation_dict   = "cover@first_person@weapon@grenade";
								const char* animation = "low_l_throw_long";
								if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, animation_dict, animation, 3)) {
									STREAMING::REQUEST_ANIM_DICT(animation_dict);
									if (STREAMING::HAS_ANIM_DICT_LOADED((animation_dict))) {
										TASK::TASK_PLAY_ANIM(self::ped, animation_dict, animation, 8.00f, 8.00f, -1, 48, 0.f, FALSE, FALSE, FALSE);
										MISC::FORCE_LIGHTNING_FLASH();
										play_animation_on_ped = false;
									}
								}
							}

							int bone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(self::ped, (char*)"IK_R_Hand");
							ENTITY::ATTACH_ENTITY_TO_ENTITY(entity_axe, self::ped, bone, 0, -0.05f, -0.05f, -61.f, 28.4f, -48.8f, false, false, true, true, 0, true, 0);
						}
					}
					else
					{
						if (ENTITY::IS_ENTITY_ATTACHED(entity_axe)) {
							ENTITY::DETACH_ENTITY(entity_axe, 0, true);
							if (!play_animation_on_ped) {
								const char* animation_dict = "weapons@first_person@aim_rng@generic@projectile@grenade_str";
								const char* animation = "throw_m_fb_forward";
								if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, animation_dict, animation, 3)) {
									STREAMING::REQUEST_ANIM_DICT(animation_dict);
									if (STREAMING::HAS_ANIM_DICT_LOADED((animation_dict))) {
										TASK::TASK_PLAY_ANIM(self::ped, animation_dict, animation, 8.00f, 8.00f, -1, 48, 0.f, FALSE, FALSE, FALSE);
										play_animation_on_ped = true;
									}
								}
							}
						}
					}
					PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, TRUE);
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
						axe_attacking            = true;

						Vector3 cam_coords = CAM::GET_GAMEPLAY_CAM_COORD();
						Vector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 cam_direction = math::rotation_to_direction(cam_rot);
						float distance        = 150.f;
						Vector3 multiply = cam_direction * distance;
						new_axe_flying_coords = cam_coords + multiply;
						// only for controller
						PAD::SET_CONTROL_SHAKE(0, 1, 5);
					}
				}
				else
				{
					axe_attacking         = false;
					axe_on_idle   = true;
				}
				Vector3 subtract_coords     = axe_flying_coords - axe_coords;
				Vector3 ent_velocity = ENTITY::GET_ENTITY_VELOCITY(entity_axe);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity_axe))
				{
					float speed = axe_on_idle ? 1.0f : 2.6f;
					//YES OMG

					ENTITY::APPLY_FORCE_TO_ENTITY(entity_axe,
					    3,
					    (subtract_coords.x * (speed * speed)) - ((2.01f + 2.f) * speed * 0.3f * ent_velocity.x) + 0.0f,
					    (subtract_coords.y * (speed * speed)) - (2.01f * speed * 0.3f * ent_velocity.y) + 0.0f,
					    (subtract_coords.z * (speed * speed)) - (2.01f * speed * 0.3f * ent_velocity.z) + 0.1f,
					    0.0f,
					    0.f,
					    0.f,
					    0,
					    0,
					    1,
					    1,
					    0,
					    1);
				}
				else
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity_axe);
				}
			}
		}
		virtual void on_disable() override
		{
			if (ENTITY::DOES_ENTITY_EXIST(entity_axe)) {
				ENTITY::DELETE_ENTITY(&entity_axe);
			}
		}
	};

	flying_axe
	    g_flying_axe("flyingaxe", "BACKEND_LOOPED_FLYING_AXE", "BACKEND_LOOPED_FLYING_AXE_DESC", g.weapons.flying_axe.enable);
}
