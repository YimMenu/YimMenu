#include "backend/bool_command.hpp"
#include "backend/command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/ped_animations/ped_animations_service.hpp"
#include "util/mobile.hpp"
#include "util/string_operations.hpp"
#include "util/vehicle.hpp"
#include "util/ped.hpp"

namespace big
{
	class play_animation : command
	{
		using command::command;

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1)
			{
				std::vector<std::string> suggestions;
				suggestions.push_back("stop");
				for (auto& item : g_ped_animation_service.all_saved_animations | std::views::values | std::views::join)
				{
					std::string anim_name = item.name;
					string::operations::remove_whitespace(anim_name);
					string::operations::to_lower(anim_name);
					suggestions.push_back(anim_name);
				}
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(1);
			const std::string anim_name = args[0];

			if (anim_name == "stop")
			{
				result.push<int>(-1);
				return result;
			}


			int anim_index = 0;
			for (auto& item : g_ped_animation_service.all_saved_animations | std::views::values | std::views::join)
			{
				std::string display_name = item.name;
				display_name             = string::operations::remove_whitespace(display_name);
				display_name             = string::operations::to_lower(display_name);
				
				if (display_name.find(anim_name) != std::string::npos)
				{
					result.push<int>(anim_index);
					break;
				}
				anim_index++;
			}

			return result;
		}

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx) override
		{
			const auto anim_index = args.get<int>(0);

			if (anim_index == -1)
			{
				TASK::CLEAR_PED_TASKS(self::ped);
				return;
			}

			int count             = 0;
			for (auto& item : g_ped_animation_service.all_saved_animations | std::views::values | std::views::join)
			{
				if (count == anim_index)
					g_ped_animation_service.play_saved_ped_animation(item, self::ped);

				count++;
			}

		}
	};

	play_animation g_play_animation("anim", "PLAY_ANIMATION", "PLAY_ANIMATION_DESC", 1);
}
