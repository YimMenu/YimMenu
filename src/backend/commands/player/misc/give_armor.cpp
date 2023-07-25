#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/pickups/pickup_service.hpp"
#include "util/globals.hpp"

namespace big
{
	class give_armor : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			g_pickup_service->give_armour(player->id());
		}
	};

	give_armor g_give_armor("givearmor", "GIVE_ARMOR", "GIVE_ARMOR_DESC", 0);
}