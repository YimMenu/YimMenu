#include "steal_identity.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/ped.hpp"

namespace big
{
	void steal_identity::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		ped::steal_identity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()));
	}
}
