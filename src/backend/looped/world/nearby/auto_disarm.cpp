#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/pools.hpp"

namespace big
{
	class auto_disarm : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_notification_service.push("VIEW_WORLD_AUTO_DISARM"_T.data(), "VIEW_WORLD_AUTO_DISARM_NOTIFY"_T.data());
		}

		virtual void on_tick() override
		{
			for (auto ped : pools::get_all_peds())
			{
				if (!ped)
					continue;

				auto handle = g_pointers->m_gta.m_ptr_to_handle(ped);

				if (!PED::IS_PED_A_PLAYER(handle) && ENTITY::DOES_ENTITY_EXIST(PED::GET_PED_TARGET_FROM_COMBAT_PED(handle, false)))
				{
					if (entity::take_control_of(handle, 0))
					{
						if (WEAPON::IS_PED_ARMED(handle, 1 | 2 | 4))
							WEAPON::REMOVE_ALL_PED_WEAPONS(handle, false);

						if (g.world.nearby.auto_disarm.neutralize)
							TASK::TASK_STAND_STILL(handle, -1);
					}
				}
			}
		}
	};

	auto_disarm g_auto_disarm("autodisarm", "BACKEND_LOOPED_WORLD_NEARBY_AUTO_DISARM", "BACKEND_LOOPED_WORLD_NEARBY_AUTO_DISARM_DESC", g.world.nearby.auto_disarm.enable);
}
