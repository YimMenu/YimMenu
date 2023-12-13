#include "backend/looped_command.hpp"
#include "pointers.hpp"

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

	force_relay_connections g_force_relay_connections("forcerelays", "FORCE_RELAY_CXN", "FORCE_RELAY_CXN_DESC",
	    g.protections.force_relay_connections);
}
