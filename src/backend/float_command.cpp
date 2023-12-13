#include "float_command.hpp"

namespace big
{
	float_command::float_command(const std::string& name, const std::string& label, const std::string& description, float& value, float lower_bound, float upper_bound) :
	    command(name, label, description, 1),
	    m_value(value),
	    m_lower_bound(lower_bound),
	    m_upper_bound(upper_bound)
	{
	}

    void float_command::execute(const command_arguments& args, const std::shared_ptr<command_context> ctx)
    {
        m_value = args.get<float>(0);
    }

	std::optional<command_arguments> float_command::parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		command_arguments result(1);
		float value = std::atof(args[0].c_str());

		if (value < m_lower_bound || value > m_upper_bound)
		{
			ctx->report_error(std::format("Value {} is not between {} and {} in command {}", value, m_lower_bound, m_upper_bound, m_name));
			return std::nullopt;
		}

		result.push(value);
		return result;
	}
}