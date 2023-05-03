#pragma once

#include "backend/command.hpp"

namespace big
{
	class boat_pickup : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	class ballistic_armor : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline boat_pickup g_boat_pickup("boatpickup", "Request Boat Pickup", "Request a boat pickup", 0);
		inline ballistic_armor g_ballistic_armor("ballisticarmor", "Request Ballistic Equipment", "Requests ballistic equipment which includes ballistic armor and an minigun", 0);
	}
}
