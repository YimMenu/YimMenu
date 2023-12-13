#pragma once
#include "core/enums.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class command_context
	{
	public:
		virtual player_ptr get_sender() const                       = 0;
		virtual CommandAccessLevel get_access_level() const         = 0;
		virtual void report_output(const std::string& output) const = 0;
		virtual void report_error(const std::string& error) const   = 0;
	};
}