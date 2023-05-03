#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class disable_phone : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline disable_phone
		    g_disable_phone("nophone", "Disable Phone", "Blocks phone and stops all phone calls", g.tunables.disable_phone);
	}
}
