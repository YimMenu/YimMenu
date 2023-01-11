#include "console_service.hpp"

namespace big
{
    console_service::console_service()
    {
        g_console_service = this;
    }

    console_service::~console_service() 
    {
        g_console_service = nullptr;
    }

    std::vector<command*> console_service::get_suggestions(const std::string_view search)
    {
        std::vector<command*> found_commands{};
        for (auto& [k, command] : g_commands)
        {
            std::size_t matched = command->get_name().find(search);
            if (std::string::npos == matched)
                matched = command->get_label().find(search);

            if (std::string::npos != matched)
                found_commands.push_back(command);
        }

        return found_commands;
    }
}