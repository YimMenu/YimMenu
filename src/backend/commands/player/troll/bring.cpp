#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	class bring : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			teleport::bring_player(player);
		}
	};

	class bring_all : command
	{
		using command::command;

		virtual void execute(const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			for (auto& player : g_player_service->players())
				g_fiber_pool->queue_job([player]() {
					teleport::bring_player(player.second);
				});
		}
	};

	bring g_bring("bring", "BRING", "BRING_DESC", 0, false);
	bring_all g_bring_all("bringall", "BRING_ALL", "BRING_ALL_DESC", 0, false);
}