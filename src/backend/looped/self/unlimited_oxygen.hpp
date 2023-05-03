#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class unlimited_oxygen : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline unlimited_oxygen g_unlimited_oxygen("infoxy", "Unlimited Oxygen", "Allows you to stay underwater without losing oxygen",
		    g.self.unlimited_oxygen);
	}
}
