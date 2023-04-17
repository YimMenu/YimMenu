#pragma once
#include "command_context.hpp"

namespace big
{
	class default_command_context : public command_context
	{
	public:
		virtual player_ptr get_sender() const override;
		virtual CommandAccessLevel get_access_level() const override;
		virtual void report_output(const std::string& output) const override;
		virtual void report_error(const std::string& error) const override;
		default_command_context(){};
	};
}