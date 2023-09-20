#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class suicide : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			auto godmode_backup = g.self.god_mode;
			g.self.god_mode     = false;
			ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
			g.self.god_mode = godmode_backup;
		}
	};

	suicide g_suicide("suicide", "SUICIDE", "SUICIDE_DESC", 0);
}