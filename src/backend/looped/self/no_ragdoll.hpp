#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class no_ragdoll : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_ragdoll g_no_ragdoll("noragdoll", "No Ragdoll", "Prevents you from ragdolling", g.self.no_ragdoll);
	}
}
