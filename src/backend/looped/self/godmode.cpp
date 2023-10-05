#include "backend/looped_command.hpp"
#include "core/settings.hpp"
#include "natives.hpp"

namespace big
{
	class godmode : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player == nullptr)
				return;

			g_local_player->m_damage_bits = static_cast<int>(eEntityProofs::GOD);
		}

		virtual void on_disable() override
		{
			g_local_player->m_damage_bits = 0;
		}
	};

	godmode g_godmode("godmode", "God Mode", "Prevents you from taking any form of damage", g.self.god_mode);
}