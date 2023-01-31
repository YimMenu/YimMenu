#include "backend/command.hpp"

namespace big
{
	class fast_quit : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			exit(0);
		}
	};

	fast_quit g_fast_quit("fastquit", "Rage Quit", "We all have bad times sometimes. Close your GTA instant.", 0);
}
