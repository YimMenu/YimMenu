#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class triggerbot : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline triggerbot g_triggerbot("triggerbot", "Triggerbot", "Shoots at a ped with fast ease", g.weapons.triggerbot);
	}
}
