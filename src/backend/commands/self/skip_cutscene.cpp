#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class skip_cutscene : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
	};

	skip_cutscene g_skip_cutscene("skipcutscene", "SKIP_CUTSCENE", "SKIP_CUTSCENE_DESC", 0);
}