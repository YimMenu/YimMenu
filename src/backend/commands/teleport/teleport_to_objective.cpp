#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_objective : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			teleport::to_objective();
		}
	};

	teleport_to_objective g_teleport_to_objective("objectivetp", "VIEW_HOTKEY_SETTINGS_TELEPORT_TO_OBJECTIVE", "BACKEND_TELEPORT_TO_OBJECTIVE_DESC", 0);
}