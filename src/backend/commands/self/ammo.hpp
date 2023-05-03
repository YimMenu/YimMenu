#pragma once

#include "backend/command.hpp"

namespace big
{
	class fill_ammo : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline fill_ammo g_fill_ammo("fillammo", "Fill Ammo", "Fills all of your ammo.", 0);
	}
}
