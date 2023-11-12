#pragma once
#include "core/enums.hpp"

namespace big
{
	struct SessionType
	{
		eSessionType id;
		const char name[22];
	};

	const SessionType sessions[] = {
	    {eSessionType::JOIN_PUBLIC, "Join Public Session"},
	    {eSessionType::NEW_PUBLIC, "New Public Session"},
	    {eSessionType::CLOSED_FRIENDS, "Closed Friend Session"},
	    {eSessionType::INVITE_ONLY, "Invite Only Session"},
	};
}