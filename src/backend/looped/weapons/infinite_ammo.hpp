#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class infinite_ammo : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline infinite_ammo g_infinite_ammo("infammo", "Infinite Ammo", "Never run out of ammo again", g.weapons.infinite_ammo);
	}
}
