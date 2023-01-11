#pragma once
#include "backend/command.hpp"

namespace big
{
    class console_service
    {
    public:
        console_service();
        ~console_service();

        std::vector<command*> get_suggestions(std::string_view);
    };

    inline console_service* g_console_service{};
}