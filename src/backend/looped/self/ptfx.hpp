#pragma once

#include "backend/looped_command.hpp"

namespace big
{

	class ptfx_looped : public looped_command
	{
		using looped_command::looped_command;

		void show_player_ptfx_effect(const char* fx_name, const char* name);

		void show_vehicle_ptfx_effect(const char* fx_name, const char* name);

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline ptfx_looped
		    g_ptfx_looped("ptfx", "Enable PTFX", "Show nice PTFX Effects on your character", g.self.ptfx_effects.show);
	}
}
