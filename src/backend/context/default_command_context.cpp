#include "default_command_context.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	player_ptr default_command_context::get_sender() const
	{
		return g_player_service->get_self();
	}

	CommandAccessLevel default_command_context::get_access_level() const
	{
		return CommandAccessLevel::ADMIN;
	}

	void default_command_context::report_output(const std::string& output) const
	{
		g_notification_service.push("BACKEND_COMMAND"_T.data(), output);
	}

	void default_command_context::report_error(const std::string& error) const
	{
		g_notification_service.push_error("BACKEND_COMMAND"_T.data(), error);
	}
}
