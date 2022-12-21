#pragma once
#include "bool_command.hpp"

namespace big
{
	class looped_command : public bool_command
	{
		bool m_last_enabled = false;

	protected:
		virtual void execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		looped_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle);

		virtual void on_enable() {};
		virtual void on_disable() {};
		virtual void on_tick() = 0;
		virtual void refresh() override;

		void enable();
		void disable();
	};

	inline std::vector<looped_command*> g_looped_commands;
}