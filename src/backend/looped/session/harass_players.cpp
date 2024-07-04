#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class harass_players : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			for (auto& player : g_player_service->players())
				NETWORK::NETWORK_CONCEAL_PLAYER(player.second->id(), false, false); // disable interior instance separation
		}

		virtual void on_tick() override
		{
		}
	};

	harass_players g_harass_players("harass", "HARASS_PLAYERS", "HARASS_PLAYERS_DESC", g.session.harass_players);
}
