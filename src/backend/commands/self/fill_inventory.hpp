#pragma once

#include "backend/command.hpp"

namespace big
{
	class fill_inventory : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline fill_inventory g_fill_inventory("fillsnacks", "Fill Inventory", "Refills snacks and armor", 0);
	}
}
