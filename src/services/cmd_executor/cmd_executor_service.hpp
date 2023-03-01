#pragma once
#include "backend/command.hpp"
#include "core/enums.hpp"

namespace big
{
    class cmd_executor
    {
    public:
        cmd_executor();
        ~cmd_executor();

        std::vector<command*> get_suggestions(std::string_view, int limit = 7);
    };

    inline cmd_executor* g_cmd_executor_service{};
}