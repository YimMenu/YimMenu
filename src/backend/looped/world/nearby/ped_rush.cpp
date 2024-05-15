#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class ped_rush : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 10.0f);
			}
		}

		virtual void on_disable() override //Set the peds back to their normal speed
		{
			for (auto ped : entity::get_entities(false, true))
			{
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 1.0f);
			}
		}
	};

	ped_rush g_ped_rush("pedrush", "BACKEND_LOOPED_WORLD_PED_RUSH", "BACKEND_LOOPED_WORLD_PED_RUSH_DESC", g.world.nearby.ped_rush);
}