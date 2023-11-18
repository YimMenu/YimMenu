#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script.hpp"

namespace big
{
	class modify_gravity : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*g_pointers->m_gta.m_gravity_level = g.world.gravity.current_gravity;
			g_pointers->m_gta.m_set_gravity_level(0);
		}

		virtual void on_disable() override
		{
			*g_pointers->m_gta.m_gravity_level = 9.8f;
			g_pointers->m_gta.m_set_gravity_level(0);
		}
	};

	modify_gravity g_modify_gravity("modifygravity", "BACKEND_LOOPED_WORLD_MODIFY_GRAVITY", "BACKEND_LOOPED_WORLD_MODIFY_GRAVITY_DESC", g.world.gravity.modify_gravity);
}