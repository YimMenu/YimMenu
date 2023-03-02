#pragma once
#include "command.hpp"

namespace big
{
	class int_command : command
	{
	protected:
		int& m_value;
		int m_lower_bound;
		int m_upper_bound;

		virtual void execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		int_command(const std::string& name, const std::string& label, const std::string& description, int& value, int lower_bound, int upper_bound);
		inline int& get_value()
		{
			return m_value;
		}
	};
}