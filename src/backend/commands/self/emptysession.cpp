#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class empty_session : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			NETWORK::NETWORK_BAIL(16, 0, 0);
		}
	};

	empty_session g_emptysession("emptysession", "Empty Session", "Keeps you in the same session while disconnecting from other players", 0);
}