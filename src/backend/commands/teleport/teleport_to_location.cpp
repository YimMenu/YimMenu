#include "backend/bool_command.hpp"
#include "backend/command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/custom_teleport/custom_teleport_service.hpp"
#include "util/string_operations.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_location : command
	{
		using command::command;

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1)
			{
				std::vector<std::string> suggestions;

				for (auto& location : g_custom_teleport_service.all_saved_locations | std::views::values | std::views::join)
				{
					std::string name = location.name;
					string::operations::to_lower(name);
					string::operations::remove_whitespace(name);
					suggestions.push_back(name);
				}
			
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			m_num_args = 6; // This is retarded but it works
			command_arguments result(6);
			const std::string location_name = args[0];

			for (auto& location : g_custom_teleport_service.all_saved_locations | std::views::values | std::views::join)
			{
				std::string name = location.name;
				string::operations::to_lower(name);
				string::operations::remove_whitespace(name);

				if (name.find(location_name) != std::string::npos)
				{
					result.push<float>(location.x);
					result.push<float>(location.y);
					result.push<float>(location.z);
					result.push<float>(location.yaw);
					result.push<float>(location.pitch);
					result.push<float>(location.roll);
					return result;
				}
			}

			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx) override
		{
			const float x = args.get<float>(0);
			const float y = args.get<float>(1);
			const float z = args.get<float>(2);
			const float yaw = args.get<float>(3);
			const float pitch = args.get<float>(4);
			const float roll = args.get<float>(5);

			teleport::teleport_player_to_coords(g_player_service->get_self(), Vector3(x, y, z), Vector3(yaw, pitch, roll));
			m_num_args = 1; // This is retarded but it works
		}
	};

	teleport_to_location g_teleport_to_location("location", "Teleport To Location", "TELEPORT_TO_LOCATION_DESC", 1);
}
