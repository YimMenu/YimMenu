#include "chat_command_context.hpp"

#include "hooking.hpp"
#include "util/notify.hpp"

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
		g_fiber_pool->queue_job([this, output] {
			char msg[265]{};
			msg[0] = g.session.chat_output_prefix;
			msg[1] = ' ';
			strncpy(msg + 2, output.c_str(), sizeof(msg) - 2);

			if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_send_chat_ptr,
			        g_player_service->get_self()->get_net_data(),
			        msg,
			        false))
				notify::draw_chat(msg, g_player_service->get_self()->get_name(), false);
		});
	}

	void chat_command_context::report_error(const std::string& error) const
	{
		report_output(error);
	}
}