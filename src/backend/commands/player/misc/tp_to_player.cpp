#include "backend/player_command.hpp"
#include "util/teleport.hpp"

namespace big
{
	class tp_to_player : player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1 || arg == 2)
			{
				std::vector<std::string> suggestions;
				for (auto& [_, player] : g_player_service->players())
				{
					suggestions.push_back(player->get_name());
				}
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(2);
			player_ptr sender = g_player_service->get_by_name_closest(args[0]);
			player_ptr target = g_player_service->get_by_name_closest(args[1]);

			if (!sender || !target)
			{
				g_notification_service.push_error("Teleport", "Invalid player name(s).");
				return std::nullopt;
			}

			result.push(sender->id());
			result.push(target->id());

			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			auto sender = g_player_service->get_by_id(_args.get<uint8_t>(0));
			auto target = g_player_service->get_by_id(_args.get<uint8_t>(1));

			if (target && target->get_ped()
			    && target->get_ped()->get_position())
			{
				auto coords     = target->get_ped()->get_position();
				Vector3 coords_ = {coords->x, coords->y, coords->z};
				teleport::teleport_player_to_coords(sender, coords_);
				g_notification_service.push(sender->get_name(), "Teleported to " + std::string(target->get_name()));
			}
		}
	};

	tp_to_player tp_to_player_shortcut("tp", "Teleport to Player", "Teleport first player to the second", 1);
}