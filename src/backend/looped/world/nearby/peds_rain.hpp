#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class ped_rain : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline ped_rain g_ped_rain("pedrain", "Rain Peds", "Will pour down and rain nearby peds.", g.world.nearby.ped_rain);
	}
}
