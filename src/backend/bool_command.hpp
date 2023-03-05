#pragma once
#include "command.hpp"

namespace big
{
	class bool_command : public command
	{
	protected:
		bool& m_toggle;
		bool m_show_notify;
		virtual void execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		bool_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle, bool show_notify = true);
		inline bool& is_enabled()
		{
			return m_toggle;
		}

		virtual void refresh(){};
		virtual void enable()
		{
			m_toggle = true;
		};
		virtual void disable()
		{
			m_toggle = false;
		};
	};
}