#include "cmd_executor_service.hpp"

namespace big
{
    cmd_executor::cmd_executor()
    {        
        g_cmd_executor_service = this;
    }

    cmd_executor::~cmd_executor() 
    {
        g_cmd_executor_service = nullptr;
    }

    std::vector<command*> cmd_executor::get_suggestions(const std::string_view search, const int limit)
    {
		std::vector<command*> found_commands{};
		for (auto& [k, command] : g_commands)
		{
			if(command->get_label().length() == 0) continue;

			if(command->get_name().contains(search))
				found_commands.push_back(command);
			else if (command->get_label().contains(search))
				found_commands.push_back(command);

			// apply our maximum vector size..
			if(found_commands.size() > limit) break;
		}

		return found_commands;
    }
}