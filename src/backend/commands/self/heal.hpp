#pragma once

#include "backend/command.hpp"

namespace big
{
	class heal : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline heal g_heal("heal", "Heal", "Restores full health and armor", 0);
	}
}
