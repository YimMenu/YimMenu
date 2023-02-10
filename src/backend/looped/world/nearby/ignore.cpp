#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class ignore : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{

			for (auto ped : entity::get_entities(false, true))
			{
				if (!PED::GET_PED_CONFIG_FLAG(ped, 17, true)) { // Flag 17 = PED_FLAG_BLOCK_NON_TEMPORARY_EVENTS
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
					TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				}
			}
		}
	};

	ignore g_ignore("pedsignore", "Ignore", "Nearby peds will ignore you and become oblivious to your actions.", g.world.nearby.ignore);
	
}