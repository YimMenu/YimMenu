#include "backend/looped_command.hpp"
#include "core/globals.hpp"

#include <algorithm>
#include <vector>


namespace big
{
	class admin_check : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			std::vector<std::string> admin_names = {"admin1", "admin2", "admin3"};
			g_player_service->iterate([&](const player_ptr& plyr) {
				auto found = std::find(admin_names.begin(), admin_names.end(), plyr->get_name());
				if (found != admin_names.end())
				{
					g_notification_service->push_warning("Potential Admin Found!", "A potential admin has been found in your lobby!")
				}
			})
		}
	}
}