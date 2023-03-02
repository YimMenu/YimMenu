#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class ignore : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override//should help for any stragglers that aren't set by the tick (aka current event)
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, true);
			PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, true);
		}

		virtual void on_tick() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				if (!PED::GET_PED_CONFIG_FLAG(ped, 17, true))
				{// Flag 17 = PED_FLAG_BLOCK_NON_TEMPORARY_EVENTS
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
					TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				}
			}
		}

		virtual void on_disable() override
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, false);
			PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, false);
		}
	};

	ignore g_ignore("pedsignore", "Ignore", "Nearby peds will ignore you and become oblivious to your actions.",
	    g.world.nearby.ignore);

}