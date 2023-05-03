#include "join_ceo.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_function.hpp"

namespace big
{
	void join_ceo::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		scr_functions::join_ceo({player->id(), 0, false, false});
	}
}
