#pragma once

#include "backend/command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class clean_player : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline clean_player g_clean_player("clean", "Clean Player", "Cleans the player of wetness and decals", 0);
	}
}
