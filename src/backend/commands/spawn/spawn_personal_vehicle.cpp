#include "backend/bool_command.hpp"
#include "backend/command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "util/string_operations.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class spawn_personal_vehicle : command
	{
		using command::command;

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (g_mobile_service->personal_vehicles().empty())
				g_mobile_service->refresh_personal_vehicles();

			if (arg == 1)
			{
				std::vector<std::string> suggestions;
				for (auto& item : g_mobile_service->personal_vehicles() | std::ranges::views::values)
				{
					std::string display_name = item.get()->get_display_name();
					display_name             = string::operations::remove_whitespace(display_name);
					display_name             = string::operations::to_lower(display_name);
					suggestions.push_back(display_name);
				}
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(1);
			const std::string personal_veh_display_name = args[0];

			for (auto& item : g_mobile_service->personal_vehicles() | std::ranges::views::values)
			{
				std::string display_name = item.get()->get_display_name();
				display_name             = string::operations::remove_whitespace(display_name);
				display_name             = string::operations::to_lower(display_name);
				if (display_name.find(personal_veh_display_name) != std::string::npos)
				{
					result.push(item->get_id());
					break;
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
			const auto personal_veh_index = args.get<int>(0);
			mobile::mechanic::summon_vehicle_by_index(personal_veh_index);
		}
	};

	spawn_personal_vehicle g_spawn_personal_vehicle("spawnpv", "GUI_TAB_SPAWN_VEHICLE", "BACKEND_SPAWN_VEHICLE_DESC", 1);
}
