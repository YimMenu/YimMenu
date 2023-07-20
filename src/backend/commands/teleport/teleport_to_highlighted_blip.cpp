#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_highlighted_blip : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			teleport::to_highlighted_blip();
		}
	};

	teleport_to_highlighted_blip g_teleport_to_highlighted_blip("highlighttp", "Teleport to Selected Blip", "Teleports you to whichever blip you have in your crosshairs on the map.", 0);
}