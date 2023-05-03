#pragma once

#include "backend/command.hpp"

namespace big
{
	class bring_personal_vehicle : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline bring_personal_vehicle g_bring_personal_vehicle("bringpv", "Bring Personal Vehicle", "Teleports your PV near you", 0);
	}
}
