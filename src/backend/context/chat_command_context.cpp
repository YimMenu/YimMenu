#include "chat_command_context.hpp"

#include "fiber_pool.hpp"
#include "hooking/hooking.hpp"
#include "util/chat.hpp"

namespace big
{
	chat_command_context::chat_command_context(player_ptr player) :
	    m_player(player)
	{
	}

	player_ptr chat_command_context::get_sender() const
	{
		return m_player;
	}

	CommandAccessLevel chat_command_context::get_access_level() const
	{
		if (!m_player->is_valid())
			return CommandAccessLevel::NONE;

		return m_player->command_access_level.value_or(g.session.chat_command_default_access_level);
	}

	void chat_command_context::report_output(const std::string& output) const
	{
		chat::send_message(output, this->get_sender(), true, true);
	}

	void chat_command_context::report_error(const std::string& error) const
	{
		report_output(error);
	}
}