#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class high_alert : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				PED::SET_PED_HIGHLY_PERCEPTIVE(ped, true);
				PED::SET_PED_HEARING_RANGE(ped, 1000.0);
				PED::SET_PED_SEEING_RANGE(ped, 1000.0);
				PED::SET_PED_VISUAL_FIELD_MIN_ANGLE(ped, 1000.0);
			}
		}
	};

	high_alert g_high_alert("highalert", "High Alert", "Not the CoD perk.", g.world.nearby.high_alert);

}