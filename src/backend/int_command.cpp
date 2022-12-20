#include "int_command.hpp"

namespace big
{
	int_command::int_command(const std::string& name, int& value, int lower_bound, int upper_bound) :
		command(name, 1),
		m_value(value),
		m_lower_bound(lower_bound),
		m_upper_bound(upper_bound)
	{
	}

	void int_command::execute(const std::vector<std::uint64_t>& args, const command_context&)
	{
		m_value = args[0];
	}

	std::optional<std::vector<std::uint64_t>> int_command::parse_args(const std::vector<std::string>& args, const command_context& ctx)
	{
		std::vector<std::uint64_t> result;
		int value = std::atoi(args[0].c_str());

		if (value < m_lower_bound || value > m_upper_bound)
		{
			ctx.report_error(std::format("Value {} is not between {} and {} in command {}", value, m_lower_bound, m_upper_bound, m_name));
			return std::nullopt;
		}

		result.push_back(value);
		return result;
	}
}