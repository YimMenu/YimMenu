#pragma once

#include "backend/command.hpp"

namespace big
{
	class teleport_to_objective : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline teleport_to_objective g_teleport_to_objective("objectivetp", "Teleport To Objective", "Teleports you to your mission objective", 0);
	}
}
