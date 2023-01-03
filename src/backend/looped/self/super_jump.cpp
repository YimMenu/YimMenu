#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/entity.hpp"

namespace big
{
	class super_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			TASK::TASK_JUMP(self::ped, true, true, true);
		}
	};

	super_jump_looped g_super_jump_looped("superjump", "Super Jump", "Allows You To Jump Really High", g.self.super_jump);
}
