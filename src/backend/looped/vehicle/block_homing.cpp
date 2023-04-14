#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class block_homing : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player && g_local_player->m_vehicle)
				g_local_player->m_vehicle->m_is_targetable = false;
		}

		virtual void on_disable() override
		{
			if (g_local_player && g_local_player->m_vehicle)
				g_local_player->m_vehicle->m_is_targetable = true;
		}
	};

	block_homing g_block_homing("blockhoming", "Block Homing Missiles", "Prevents homing missiles from locking on to your vehicle",
	    g.vehicle.block_homing);
}
