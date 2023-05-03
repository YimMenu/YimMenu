#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class combative : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline combative g_combative("riotmode", "Riot Mode", "Make nearby peds attack eachother", g.world.nearby.combative);
	}
}
