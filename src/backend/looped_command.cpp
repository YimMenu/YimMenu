#include "looped_command.hpp"

namespace big
{
	looped_command::looped_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle) :
	    bool_command(name, label, description, toggle)
	{
		g_looped_commands.push_back(this);
	}
}