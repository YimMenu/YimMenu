#include "backend/command.hpp"

namespace big
{
	class recovery : command
	{
		using command::command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::NONE;
		}

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			ctx->report_error("Money and recovery options are not supported in YimMenu to keep Rockstar/Take Two happy. You can try Kiddion's Modest Menu (free) instead, but make sure to only get it from UnknownCheats.me, the rest are scams and may contain malware");
		}
	};

	recovery g_money("money", "", "", 0);
	recovery g_cash("cash", "", "", 0);
	recovery g_drop("drop", "", "", 0);
	recovery g_stats("stats", "", "", 0);
}