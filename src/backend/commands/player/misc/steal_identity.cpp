#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/ped.hpp"

namespace big
{
	class steal_identity : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			ped::steal_identity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()));
		}
	};

	steal_identity g_steal_identity("copymodel", "STEAL_IDENTITY", "STEAL_IDENTITY_DESC", 0, false); // do we really need this?
}