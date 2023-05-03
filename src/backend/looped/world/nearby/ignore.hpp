#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class ignore : public looped_command
	{
		using looped_command::looped_command;

		// Should help for any stragglers that aren't set by the tick (aka current event);
		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline ignore g_ignore("pedsignore", "Ignore", "Nearby peds will ignore you and become oblivious to your actions.",
		    g.world.nearby.ignore);
	}
}
