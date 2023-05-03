#pragma once

#include "backend/command.hpp"

namespace big
{
	class repairpv : public command
	{
		using command::command;
		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		repairpv g_repairpv("repairpv", "Repair PV", "Repairs your currently active personal vehicle", 0);
	}
}
