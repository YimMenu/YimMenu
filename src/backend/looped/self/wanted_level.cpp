#include "backend/command.hpp"
#include "backend/looped_command.hpp"
#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	bool user_updated_wanted_level = false;
	static int prev_max_wanted_level   = 5;

	class clear_wanted : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			// If we're never wanted... don't bother since there is no wanted level to clear anyway (this button won't even be shown if never_wanted is enabled)
			if (g.self.never_wanted)
				return;

			// Clear current wanted level
			g_local_player->m_player_info->m_wanted_level = 0;
			g_local_player->m_player_info->m_is_wanted = false;

			// Keep the lock if it's on, but reset the wanted level
			g.self.wanted_level = 0;
		}
	};

	clear_wanted g_clear_wanted("clearwantedself", "CLEAR_WANTED_LEVEL", "CLEAR_WANTED_LEVEL_DESC_SELF", 0);

	class never_wanted : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			// Clear current wanted level
			g_local_player->m_player_info->m_wanted_level = 0;
			g_local_player->m_player_info->m_is_wanted    = false;

			// Account for situations like Fort Zancudo that continuously spam a high wanted level and can "flicker" the wanted level
			PLAYER::SET_MAX_WANTED_LEVEL(0);

			// Since we're hiding the force wanted checkbox and wanted slider, we don't need to do anything else
			g.self.wanted_level       = 0;
			g.self.force_wanted_level = false;
		}

		virtual void on_enable() override
		{
			// Save the previous wanted level so we can restore it on disable, but don't soft lock us into a 0 since that wouldn't really make sense 
			if (PLAYER::GET_MAX_WANTED_LEVEL() != 0)
				prev_max_wanted_level = PLAYER::GET_MAX_WANTED_LEVEL();

			// Set the max wanted level to 0 here as well, even though we're setting it in on_tick
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}

		virtual void on_disable() override
		{
			// Restore the previous wanted level
			// NOTE: Since Never Wanted could have been set at any point, there is no guarantee that the prev_max_wanted_level is still valid for wherever the player is

			PLAYER::SET_MAX_WANTED_LEVEL(prev_max_wanted_level);
		}
	};

	never_wanted g_never_wanted("neverwanted", "NEVER_WANTED", "NEVER_WANTED", g.self.never_wanted);

	void looped::self_wanted()
	{
		// Don't do anything if we're supposed to be never wanted (this slider won't be shown if never_wanted is enabled)
		if (g.self.never_wanted)
			return;

		if (g_local_player && g_local_player->m_player_info)
		{
			// We only want the wanted level to update when the player changed it via the ImGui slider
			if (user_updated_wanted_level)
			{
				g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;

				if (g.self.wanted_level == 0)
					g_local_player->m_player_info->m_is_wanted = false;
				else
					g_local_player->m_player_info->m_is_wanted = true;

				// I don't know if ImGui resets this every tick, let's assume it doesn't
				user_updated_wanted_level = false;
				return;
			}

			// Otherwise, if we're locking the wanted level, then just keep it consistently at what the player set
			if (g.self.force_wanted_level)
			{
				g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;

				if (g.self.wanted_level == 0)
					g_local_player->m_player_info->m_is_wanted = false;
				else
					g_local_player->m_player_info->m_is_wanted = true;
			}

			if (!user_updated_wanted_level && !g.self.force_wanted_level)
			{
				// If the player hasn't updated the wanted level and we're not locking, then YimMenu should update its own slider value to reflect the actual in-game wanted level since it may have changed
				g.self.wanted_level = g_local_player->m_player_info->m_wanted_level;
			}
		}
	}
}