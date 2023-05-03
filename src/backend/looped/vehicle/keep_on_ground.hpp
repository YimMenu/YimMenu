#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class keep_on_ground : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline keep_on_ground g_keep_on_ground("keeponground", "Keep On Ground", "Makes it so your vehicle is always on the ground on all four wheels",
		    g.vehicle.keep_on_ground);
	}
}
