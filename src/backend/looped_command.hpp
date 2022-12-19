#pragma once
#include "command.hpp"

namespace big
{
	class looped_command : public command
	{
		bool m_last_enabled = false;
		bool& m_toggle;

	protected:
		virtual void execute(const std::vector<std::uint64_t>& args) override;

	public:
		looped_command(const std::string& name, bool& toggle);

		virtual void on_enable() {};
		virtual void on_disable() {};
		virtual void on_tick() = 0;

		void enable();
		void disable();
		void refresh();
		
		inline bool& is_enabled() { return m_toggle; }
	};

	inline std::vector<looped_command*> g_looped_commands;
}