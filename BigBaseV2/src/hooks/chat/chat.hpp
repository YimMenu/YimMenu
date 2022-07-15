#pragma once

namespace big
{
    struct chatmessage {
        std::string message;
        std::string player_name;
        int network_time;
    };

	static std::vector<chatmessage> all_messages;

    static void log_msg(std::string message, std::string name) {
        all_messages.push_back({ message, name, 0 });
    }
}