#pragma once
#include "bool_command.hpp"

namespace big
{
	class looped_command : public bool_command
	{
	public:
		looped_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle);

		virtual void on_tick() = 0;
	};

	inline std::vector<looped_command*> g_looped_commands;
}