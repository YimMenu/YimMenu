#include "give_health.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "services/pickups/pickup_service.hpp"
#include "util/globals.hpp"

namespace big
{
	CommandAccessLevel give_health::get_access_level()
	{
		return CommandAccessLevel::FRIENDLY;
	}

	void give_health::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		g_pickup_service->give_player_health(player->id());
	}
}
