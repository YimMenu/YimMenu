#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class ped_rush : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		//Set the peds back to their normal speed
		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline ped_rush g_ped_rush("pedrush", "Ped Rush", "Makes the nearby peds move with a purpose.", g.world.nearby.ped_rush);
	}
}
