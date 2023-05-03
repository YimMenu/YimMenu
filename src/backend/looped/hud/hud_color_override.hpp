#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class hudcolor_looped : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline hudcolor_looped g_hudcolor_looped("hudcolor", "Override HUD Color", "Override HUD colors", g.self.hud.color_override);
	}
}
