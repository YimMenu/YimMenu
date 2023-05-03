#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class fast_respawn : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline fast_respawn
		    g_fast_respawn("fastrespawn", "Instant Respawn", "Makes you respawn instantly when you die", g.self.fast_respawn);
	}
}
