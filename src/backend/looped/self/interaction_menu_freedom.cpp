#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class interaction_menu_freedom : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*scr_globals::interaction_menu_access.as<int*>() = 1; // sets itself to the original value every frame while you're in the interaction menu, so no need for a reset
		}
	};

	interaction_menu_freedom g_interaction_menu_freedom("interactionmenufreedom", "INTERACTION_MENU_FREEDOM", "INTERACTION_MENU_FREEDOM_DESC", g.self.interaction_menu_freedom);
}