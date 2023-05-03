#pragma once

#include "backend/command.hpp"

namespace big
{
	class skip_cutscene : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline skip_cutscene g_skip_cutscene("skipcutscene", "Skip Cutscene", "Skips the currently playing cutscene", 0);
	}
}
