#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "core/settings/protections.hpp"

namespace big
{
	class force_relay_connections : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*g_pointers->m_gta.m_force_relay_connections = true;
		}

		virtual void on_disable() override
		{
			*g_pointers->m_gta.m_force_relay_connections = false;
		}
	};

	force_relay_connections g_force_relay_connections("forcerelays", "Force Relay Connections", "Hides your IP address by rerouting your connection through dedicated servers and other players",
	    g_protections.force_relay_connections);
}
