#pragma once

#include "backend/command.hpp"

namespace big
{
	class teleport_to_personal_vehicle : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline teleport_to_personal_vehicle g_teleport_to_personal_vehicle("pvtp", "Teleport To Personal Vehicle", "Teleports you into your PV", 0);
	}
}
