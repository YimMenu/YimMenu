#include "backend/looped_command.hpp"

namespace big
{

	class super_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{}
	};

	super_jump_looped g_super_jump_looped("superjump", "Super Jump", "Allows you to jump really high", g.self.super_jump);
}