#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/world_model.hpp"

namespace big
{
	class bullet_shield : looped_command
	{
		using looped_command::looped_command;

		Entity shield_object{};

		void detach_delete_object()
		{
			ENTITY::DETACH_ENTITY(shield_object, false, false);
			ENTITY::DETACH_ENTITY(self::ped, true, true);

			script::get_current()->yield(50ms);
			if (entity::take_control_of(shield_object))
			{
				entity::delete_entity(shield_object);
			}

			shield_object = 0;
		}

		void spawn_object()
		{
			if (ENTITY::DOES_ENTITY_EXIST(shield_object))
			{
				detach_delete_object();
			}
			else
			{
				shield_object =
				    world_model::spawn(RAGE_JOAAT("prop_storagetank_04"), {self::pos.x, self::pos.y, self::pos.z - 5}, true);
				ENTITY::SET_ENTITY_VISIBLE(shield_object, false, 0);
				ENTITY::SET_ENTITY_DYNAMIC(shield_object, false);
				ENTITY::SET_ENTITY_HAS_GRAVITY(shield_object, false);
				script::get_current()->yield(500ms);
			}
		}

		void attach_object()
		{
			ENTITY::ATTACH_ENTITY_TO_ENTITY(shield_object, self::ped, 0, 0, 0, -5, 0, 0, 0, true, false, true, false, 0, true, false);
		}

		virtual void on_tick() override
		{
			if (ENTITY::DOES_ENTITY_EXIST(shield_object))
			{
				ENTITY::SET_ENTITY_VISIBLE(shield_object, false, 0);

				if (!ENTITY::IS_ENTITY_ATTACHED(shield_object))
				{
					attach_object();
				}
			}
			else
			{
				spawn_object();
			}
		}

		virtual void on_enable() override
		{
			spawn_object();
			attach_object();
		}

		virtual void on_disable() override
		{
			detach_delete_object();
		}
	};

	bullet_shield g_bullet_shield("bulletshield", "Bullet Shield", "Activate an invisible (bullet) shield", g.self.bullet_shield);
}