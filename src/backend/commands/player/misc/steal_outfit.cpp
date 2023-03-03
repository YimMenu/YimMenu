#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/ped.hpp"

namespace big
{
	class steal_outfit : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			ped::steal_outfit(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()));
		}
	};

	steal_outfit g_steal_outfit("copyoutfit", "Steal Outfit", "Copies the player's outfit to your ped", 0, false);
}