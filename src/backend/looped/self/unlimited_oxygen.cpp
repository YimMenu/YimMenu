#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class unlimited_oxygen : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player)
				g_local_player->m_oxygen_info->m_oxygen_time = 0;
		}
	};

	unlimited_oxygen g_unlimited_oxygen("infoxy", "Unlimited Oxygen", "Allows you to stay underwater without losing oxygen", g.self.unlimited_oxygen);
}
