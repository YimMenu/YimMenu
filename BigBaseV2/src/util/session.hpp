#pragma once
#include "core/data/session_types.hpp"
#include "script_global.hpp"
#include "script.hpp"

namespace big::session
{
	void join_type(SessionType session)
	{
		if (session.id == eSessionType::LEAVE_ONLINE)
			*script_global(1312443).at(2).as<int*>() = -1;
		else
			*script_global(1312860).as<int*>() = (int)session.id;

		*script_global(1312443).as<int*>() = 1;
		script::get_current()->yield(200ms);
		*script_global(1312443).as<int*>() = 0;
	}
}