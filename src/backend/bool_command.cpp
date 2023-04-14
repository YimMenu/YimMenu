#include "bool_command.hpp"

namespace big
{
	bool_command::bool_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle, bool show_notify) :
	    command(name, label, description, std::nullopt),
	    m_toggle(toggle),
	    m_show_notify(show_notify)
	{
	}

	void bool_command::execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		if (args.size() == 0)
		{
			if (is_enabled())
			{
				m_toggle = false;

				if (m_show_notify)
					ctx->report_output(std::format("{} has been disabled", m_label));
			}
			else
			{
				m_toggle = true;

				if (m_show_notify)
					ctx->report_output(std::format("{} has been enabled", m_label));
			}
		}
		else
		{
			m_toggle = args[0];
		}

		this->refresh();
	}

	std::optional<std::vector<std::uint64_t>> bool_command::parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		std::vector<std::uint64_t> result;

		if (args.size() == 0)
			return result;

		if (args.size() > 1)
		{
			ctx->report_error(std::format("Too many arguments passed to command {}, Expected 1 or less, got {}", m_name, args.size()));
			return std::nullopt;
		}

		if (args[0] == "yes" || args[0] == "on" || args[0] == "enable" || args[0] == "true")
		{
			result.push_back(1);
			return result;
		}

		if (args[0] == "no" || args[0] == "off" || args[0] == "disable" || args[0] == "false")
		{
			result.push_back(0);
			return result;
		}

		ctx->report_error(std::format("Cannot convert\"{}\" into a boolean in command {}", args[0], m_name));
		return std::nullopt;
	}
}