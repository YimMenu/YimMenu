#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_highlighted_blip : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			teleport::to_highlighted_blip();
		}
	};

	teleport_to_highlighted_blip g_teleport_to_highlighted_blip("highlighttp", "VIEW_HOTKEY_SETTINGS_TELEPORT_TO_SELECTED", "BACKEND_TELEPORT_TO_HIGHLIGHTED_BLIP_DESC", 0);
}