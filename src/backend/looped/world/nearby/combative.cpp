#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{

	class combative : looped_command
	{
		using looped_command::looped_command;

		int id = 0;

		virtual void on_tick() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				id = PED::GET_PED_GROUP_INDEX(ped);
				if (!PED::IS_PED_A_PLAYER(ped))
				{
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, id, id);
				}
				int time = 0;
				if (!PED::IS_PED_SHOOTING(ped) || !PED::IS_PED_IN_COMBAT(ped, ped) && time <1000)
				{
					TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped, 100.f, 0);
				}
			}
		}
		virtual void on_disable() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				bool b = PED::IS_PED_A_PLAYER(ped);
				if (!b)
				{
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(255, id, id);
				}
			}
		}
	};

	combative g_combative("pedscombat", "Combative", "Nearby peds attack eachother.", g.world.nearby.combative);

}