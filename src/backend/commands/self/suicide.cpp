#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class suicide : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const command_context&)
		{
			ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
		}
	};

	suicide g_suicide("suicide", 0);
}