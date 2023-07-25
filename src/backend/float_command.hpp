#pragma once
#include "command.hpp"

namespace big
{
	class float_command : public command
	{
	protected:
		float& m_value;
		const float m_lower_bound;
		const float m_upper_bound;

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		float_command(const std::string& name, const std::string& label, const std::string& description, float& value, float lower_bound, float upper_bound);
		inline float& get_value()
		{
			return m_value;
		}
		inline float get_lower_bound()
		{
			return m_lower_bound;
		}
		inline float get_upper_bound()
		{
			return m_upper_bound;
		}
	};
}