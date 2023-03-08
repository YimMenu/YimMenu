#include "backend/looped_command.hpp"

namespace big
{

	class beast_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{}
	};

	beast_jump_looped g_beast_jump_looped("beastjump", "Beast Jump", "Allows you to jump as if you were the beast like in the Hunt the Beast event",
	    g.self.beast_jump);
}
