#include "backend/player_command.hpp"
#include "services/squad_spawner/squad_spawner.hpp"

namespace big
{
	class send_squad : player_command
	{
		using player_command::player_command;

		std::string sterilized_name(std::string name)
		{
			string::operations::remove_whitespace(name);
			string::operations::to_lower(name);
			return name;
		}

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1)
			{
				std::vector<std::string> suggestions;
				for (auto& player : g_player_service->players() | std::ranges::views::values)
				{
					suggestions.push_back(player->get_name());
				}
				return suggestions;
			}

			if (arg == 2)
			{
				std::vector<std::string> suggestions;
				for (auto& item : g_squad_spawner_service.m_templates)
				{
					suggestions.push_back(sterilized_name(item.m_name));
				}
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(2);

			auto proxy_value = get_argument_proxy_value(args[0]);

			if (proxy_value.has_value())
			{
				result.push(proxy_value.value());
			}
			else
			{
				auto player = g_player_service->get_by_name_closest(args[0]);
				if (player == nullptr)
				{
					return std::nullopt;
				}

				result.push(player->id());
			}

			int template_index = -1;
			for (int i = 0; i < g_squad_spawner_service.m_templates.size(); i++)
			{
				if (sterilized_name(g_squad_spawner_service.m_templates[i].m_name) == args[1])
				{
					template_index = i;
					break;
				}
			}

			if (template_index == -1)
			{
				return std::nullopt;
			}

			result.push(template_index);
			
			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			auto sender =
			    _args.get<uint8_t>(0) == self::id ? g_player_service->get_self() : g_player_service->get_by_id(_args.get<uint8_t>(0));
			auto template_index = _args.get<int>(1);

			if (sender == nullptr)
			{
				return;
			}

			squad squad{};
			for (size_t i = 0; i < g_squad_spawner_service.m_templates.size(); i++)
			{
				if (i == template_index)
				{
					squad = g_squad_spawner_service.m_templates[i];
					break;
				}
			}
			
			g_squad_spawner_service.spawn_squad(squad, sender, false, {});
		}
	};

	send_squad g_send_squad("squad", "SEND_SQUAD", "SEND_SQUAD_DESC", 1);
}
