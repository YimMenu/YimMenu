#include "bool_command.hpp"

namespace big
{
	bool_command::bool_command(const std::string& name, bool& toggle) :
		command(name, 1),
		m_toggle(toggle)
	{
	}

	void bool_command::execute(const std::vector<std::uint64_t>& args, const command_context&)
	{
		m_toggle = args[0];
	}

	std::optional<std::vector<std::uint64_t>> bool_command::parse_args(const std::vector<std::string>& args, const command_context& ctx)
	{
		std::vector<std::uint64_t> result;

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

		ctx.report_error(std::format("Cannot convert\"{}\" into a boolean in command {}", args[0], m_name));
		return std::nullopt;
	}
}