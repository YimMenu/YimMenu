#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/ped.hpp"

namespace big
{
	class steal_outfit : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			ped::steal_outfit(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()));
		}
	};

	steal_outfit g_steal_outfit("copyoutfit", "STEAL_OUTFIT", "STEAL_OUTFIT_DESC", 0, false);
}