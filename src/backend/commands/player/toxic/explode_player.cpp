#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/toxic.hpp"

namespace big
{
	class explode_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			toxic::blame_explode_player(player, player, EXP_TAG_SUBMARINE_BIG, 9999.0f, true, false, 9999.0f);
		}
	};

	explode_player g_explode_player("explode", "Explode Player", "Blows the player up", 0);
}