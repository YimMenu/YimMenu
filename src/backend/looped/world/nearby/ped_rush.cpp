#include "ped_rush.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	void ped_rush::on_tick()
	{
		for (auto ped : entity::get_entities(false, true))
		{
			PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 10.0f);
		}
	}

	void ped_rush::on_disable()
	{
		for (auto ped : entity::get_entities(false, true))
		{
			PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 1.0f);
		}
	}
}
