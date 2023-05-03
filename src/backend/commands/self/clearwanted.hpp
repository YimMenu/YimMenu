#pragma once

#include "backend/command.hpp"

namespace big
{
	class clear_wanted : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline clear_wanted g_clear_wanted("clearwantedlvl", "Clear Wanted Level", "Clears your wanted level", 0);
	}
}
