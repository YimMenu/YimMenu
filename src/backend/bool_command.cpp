#include "bool_command.hpp"
#include "fiber_pool.hpp"
#include "services/translation_service/translation_service.hpp"

namespace big
{
	bool_command::bool_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle, bool show_notify) :
	    command(name, label, description, std::nullopt),
	    m_toggle(toggle),
	    m_show_notify(show_notify)
	{
		g_bool_commands.push_back(this);
	}

	void bool_command::execute(const command_arguments& args, const std::shared_ptr<command_context> ctx)
	{
		if (args.size() == 0)
		{
			if (is_enabled())
			{
				m_toggle = false;

				if (m_show_notify)
					ctx->report_output(std::format("{} has been disabled", g_translation_service.get_translation(m_label)));
			}
			else
			{
				m_toggle = true;

				if (m_show_notify)
					ctx->report_output(std::format("{} has been enabled", g_translation_service.get_translation(m_label)));
			}
		}
		else
		{
			m_toggle = args.get<bool>(0);
		}

		this->refresh();
	}

	std::optional<command_arguments> bool_command::parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		command_arguments result(1);

		if (args.size() == 0)
			return result;

		if (args.size() > 1)
		{
			ctx->report_error(std::format("Too many arguments passed to command {}, Expected 1 or less, got {}", m_name, args.size()));
			return std::nullopt;
		}

		if (args[0] == "yes" || args[0] == "on" || args[0] == "enable" || args[0] == "true")
		{
			result.push(true);
			return result;
		}

		if (args[0] == "no" || args[0] == "off" || args[0] == "disable" || args[0] == "false")
		{
			result.push(false);
			return result;
		}

		ctx->report_error(std::format("Cannot convert\"{}\" into a boolean in command {}", args[0], m_name));
		return std::nullopt;
	}

	void bool_command::enable()
	{
		if (!m_toggle)
		{
			m_toggle       = true;
			m_last_enabled = true;
			g_fiber_pool->execute_on_game_thread([this] {
				on_enable();
			});
		}
	}

	void bool_command::disable()
	{
		if (m_toggle)
		{
			m_toggle       = false;
			m_last_enabled = false;
			g_fiber_pool->execute_on_game_thread([this] {
				on_disable();
			});
		}
	}

	void bool_command::refresh()
	{
		if (m_toggle && !m_last_enabled)
		{
			m_last_enabled = true;
			g_fiber_pool->execute_on_game_thread([this] {
				on_enable();
			});
		}
		else if (!m_toggle && m_last_enabled)
		{
			m_last_enabled = false;
			g_fiber_pool->execute_on_game_thread([this] {
				on_disable();
			});
		}
	}
}