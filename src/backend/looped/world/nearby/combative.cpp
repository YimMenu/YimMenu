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
				PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, id, id); //should change by the time it goes for p2
				TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped, 100.f, 0);
			}
		}
		virtual void on_disable() override
		{
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(255, id, id);
		}
	};

	combative g_combative("combatpeds", "Combative Peds", "Nearby peds attack eachother.", g.world.nearby.combative);

}