#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class godmode_internal : public looped_command
	{
		using looped_command::looped_command;

		uint32_t last_bits = 0;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		static bool true_ref = true;
		inline godmode_internal g_godmode_internal("$$godmode", "", "", true_ref);

		inline bool_command g_godmode("godmode", "God Mode", "Prevents you from taking any form of damage", g.self.god_mode);
	}
}
