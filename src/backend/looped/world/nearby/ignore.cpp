#include "ignore.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	void ignore::on_enable()
	{
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, true);
		PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, true);
	}

	void ignore::on_tick()
	{
		for (auto ped : entity::get_entities(false, true))
		{
			// Flag 17 = PED_FLAG_BLOCK_NON_TEMPORARY_EVENTS
			if (!PED::GET_PED_CONFIG_FLAG(ped, 17, true))
			{
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			}
		}
	}

	void ignore::on_disable()
	{
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, false);
		PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, false);
	}
}
