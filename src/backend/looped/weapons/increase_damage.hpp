#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class increased_damage : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline increased_damage
		    g_increased_damage("incrdamage", "Damage Override", "Sets your damage to whatever you want", g.weapons.increase_damage);
	}
}
