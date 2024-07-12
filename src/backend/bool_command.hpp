#pragma once
#include "command.hpp"

namespace big
{
	class bool_command : public command
	{
		bool m_last_enabled = false;

	protected:
		bool& m_toggle;
		bool m_show_notify;
		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		bool_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle, bool show_notify = true);
		inline bool& is_enabled()
		{
			return m_toggle;
		}

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1) // First argument of all bool commands is true or false
			{
				return std::vector<std::string>{"true", "false"};
			}

			return std::nullopt;
		};

		virtual void on_enable(){};
		virtual void on_disable(){};
		virtual void refresh();

		virtual void enable();
		virtual void disable();
	};

	inline std::vector<bool_command*> g_bool_commands;
}