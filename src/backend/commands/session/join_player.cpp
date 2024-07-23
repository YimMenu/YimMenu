#include "backend/command.hpp"
#include "pointers.hpp"
#include "socialclub/FriendRegistry.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/api/api_service.hpp"
#include "util/session.hpp"

namespace big
{
	class join_player : command
	{
		using command::command;

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1)
			{
				std::vector<std::string> suggestions;
				for (size_t i = 0; i < g_pointers->m_gta.m_friend_registry->m_friend_count; i++)
				{
					auto f = g_pointers->m_gta.m_friend_registry->get(i);
					if (f && f->m_friend_state & (1 << 0 | 1 << 1)) // Check if online and playing same game
					{
						suggestions.push_back(f->m_name);
					}
				}

				for (const auto& player : g_player_database_service->get_sorted_players() | std::ranges::views::keys)
					suggestions.push_back(player);

				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(1);

			uint64_t rid = 0;
			// Check if the player is a friend
			for (size_t i = 0; i < g_pointers->m_gta.m_friend_registry->m_friend_count; i++)
			{
				auto f = g_pointers->m_gta.m_friend_registry->get(i);
				if (f && f->m_name == args[0])
				{
					rid = f->m_rockstar_id;
					break;
				}
			}

			// If not a friend, check if the player is in the database
			if (rid == 0)
			{
				for (const auto& [name, player] : g_player_database_service->get_sorted_players())
					if (name == args[0])
						rid = player->rockstar_id;
			}

			// If the player is not a friend or in the database, fetch rid from the API
			if (rid == 0)
			{
				auto fetched = g_api_service->get_rid_from_username(args[0], rid);

				if (!fetched || rid == 0)
				{
					ctx->report_error("Failed to fetch player's Rockstar ID from the API.");
					return std::nullopt;
				}
			}

			result.push(rid);

			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx) override
		{
			const auto rid = args.get<uint64_t>(0);
			if (rid)
			{
				session::join_by_rockstar_id(rid);
			}
		}
	};

	join_player g_join_player("joinplayer", "JOIN_PLAYER", "JOIN_PLAYER_DESC", 1);
}
