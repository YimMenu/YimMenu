#include "high_alert.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	void high_alert::on_tick()
	{
		for (auto ped : entity::get_entities(false, true))
		{
			PED::SET_PED_HIGHLY_PERCEPTIVE(ped, true);
			PED::SET_PED_HEARING_RANGE(ped, 1000.0);
			PED::SET_PED_SEEING_RANGE(ped, 1000.0);
			PED::SET_PED_VISUAL_FIELD_MIN_ANGLE(ped, 1000.0);
		}
	}
}
