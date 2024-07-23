#include "backend/player_command.hpp"
#include "services/pickups/pickup_service.hpp"

namespace big
{
	class give_ammo : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			g_pickup_service->give_player_ammo(player->id());
		}
	};

	give_ammo g_give_ammo("giveammo", "GIVE_AMMO", "GIVE_AMMO_DESC", 0);
}