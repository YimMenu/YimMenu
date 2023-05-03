#pragma once

#include "backend/command.hpp"

namespace big
{
	class suicide : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline suicide g_suicide("suicide", "Suicide", "Kills you", 0);
	}
}
