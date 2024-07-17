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
				for (auto& player : g_player_service->players() | std::ranges::views::values)
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
			// Get possible proxies for the arguments
			auto first_proxy  = get_argument_proxy_value(args[0]);
			auto second_proxy = get_argument_proxy_value(args[1]);

			// Add proxies to result if they exist
			if (first_proxy)
				result.push(first_proxy.value());
			if (second_proxy)
				result.push(second_proxy.value());

			// Return result if both proxies are valid
			if (first_proxy && second_proxy)
				return result;

			// Resolve players if proxies are not valid
			player_ptr sender, target;
			if (first_proxy == std::nullopt)
				sender = g_player_service->get_by_name_closest(args[0]);
			if (second_proxy == std::nullopt)
				target = g_player_service->get_by_name_closest(args[1]);

			// Error handling for invalid or not found players
			if ((first_proxy == std::nullopt && !sender) || (second_proxy == std::nullopt && !target))
			{
				g_notification_service.push_error(std::string("TELEPORT_PLAYER_TO_PLAYER"_T), std::string("INVALID_PLAYER_NAME_NOTIFICATION"_T));
				return std::nullopt;
			}

			// Add resolved player IDs to result
			if (sender)
				result.push(sender->id());
			if (target)
				result.push(target->id());

			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			auto sender =
			    _args.get<uint8_t>(0) == self::id ? g_player_service->get_self() : g_player_service->get_by_id(_args.get<uint8_t>(0));
			auto target =
			    _args.get<uint8_t>(1) == self::id ? g_player_service->get_self() : g_player_service->get_by_id(_args.get<uint8_t>(1));

			if (target && target->get_ped() && target->get_ped()->get_position())
			{
				auto coords     = target->get_ped()->get_position();
				Vector3 coords_ = {coords->x, coords->y, coords->z};
				teleport::teleport_player_to_coords(sender, coords_);
				auto sender_name = sender->get_name();
				auto target_name = target->get_name();
				const std::string message = std::vformat("TELEPORT_PLAYER_TO_PLAYER_NOTIFICATION"_T, std::make_format_args(sender_name, target_name));
				g_notification_service.push(std::string("TELEPORT_PLAYER_TO_PLAYER"_T), message);
			}
		}
	};

	tp_to_player tp_to_player_shortcut("tp", "TELEPORT_PLAYER_TO_PLAYER", "TELEPORT_PLAYER_TO_PLAYER_DESC", 1);
}