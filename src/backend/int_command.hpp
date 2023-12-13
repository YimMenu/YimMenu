#pragma once
#include "command.hpp"

namespace big
{
	class int_command : public command
	{
	protected:
		int& m_value;
		int m_lower_bound;
		int m_upper_bound;

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		int_command(const std::string& name, const std::string& label, const std::string& description, int& value, int lower_bound, int upper_bound);
		inline int& get_value()
		{
			return m_value;
		}
		inline int get_lower_bound()
		{
			return m_lower_bound;
		}
		inline int get_upper_bound()
		{
			return m_upper_bound;
		}
	};
}