#include "backend/command.hpp"

namespace big
{
	class fast_quit : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			exit(0);
		}
	};

	fast_quit g_fast_quit("fastquit", "VIEW_HOTKEY_SETTINGS_RAGE_QUIT", "BACKEND_FAST_QUIT_DESC", 0);
}
