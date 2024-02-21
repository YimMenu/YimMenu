#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "gui.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	class rapid_fire : looped_command
	{
		using looped_command::looped_command;

		const std::size_t m_tick_rate = 5u;
		std::size_t m_current_tick    = 0;

		/**
		 * @brief We have to limit the fire rate for some shotguns as they can fill the bullet pool and crash the game.
		 * 
		 * @return true 
		 * @return false 
		 */
		inline bool can_shoot()
		{
			bool result    = (m_current_tick == 0);
			m_current_tick = (m_current_tick + 1) % m_tick_rate;
			return result;
		}

		virtual void on_tick() override
		{
			if (!HUD::IS_PAUSE_MENU_ACTIVE() && !g_gui->is_open() && !PED::IS_PED_DEAD_OR_DYING(self::ped, true))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && can_shoot())
				{
					const auto weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self::ped, 0);
					if (!weapon_entity)
						return;

					Vector3 dim_min;
					Vector3 dim_max;
					MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(weapon_entity), &dim_min, &dim_max);

					const auto dimensions = (dim_max - dim_min) * 0.5f;
					const auto weapon_position =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon_entity, dimensions.x, 0, dimensions.z * 0.3f);

					auto camera_direction = math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
					auto camera_position  = CAM::GET_GAMEPLAY_CAM_COORD() + camera_direction;

					Vector3 end = camera_position + camera_direction * 2000.0;

					const auto raycast_handle =
					    SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camera_position.x,
					        camera_position.y,
					        camera_position.z,
					        end.x,
					        end.y,
					        end.z,
					        -1,
					        0,
					        7);
					BOOL did_raycast_hit{FALSE};
					Vector3 raycast_hit_position{};
					Vector3 raycast_surface_normal_hit_position{};
					Entity raycast_hit_entity{};
					SHAPETEST::GET_SHAPE_TEST_RESULT(raycast_handle, &did_raycast_hit, &raycast_hit_position, &raycast_surface_normal_hit_position, &raycast_hit_entity);
					if (did_raycast_hit)
					{
						end = raycast_hit_position;
					}

					Hash weapon_hash;
					WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon_hash, false);

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(weapon_position.x, weapon_position.y, weapon_position.z, end.x, end.y, end.z, WEAPON::GET_WEAPON_DAMAGE(weapon_hash, 0), true, weapon_hash, self::ped, true, false, -1.0);
				}
			}
		}
	};

	rapid_fire g_rapid_fire("rapidfire", "BACKEND_LOOPED_WEAPONS_RAPID_FIRE", "BACKEND_LOOPED_WEAPONS_RAPID_FIRE_DESC",
	    g.weapons.rapid_fire);
}
