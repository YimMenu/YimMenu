#include "backend/player_command.hpp"
#include "util/toxic.hpp"

namespace big
{
	class explode_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{ 
			toxic::blame_explode_player(player, player, EXP_TAG_SUBMARINE_BIG, 9999.0f, true, false, 9999.0f);
		}
	};

	explode_player g_explode_player("explode", "EXPLODE_PLAYER", "EXPLODE_PLAYER_DESC", 0);
}