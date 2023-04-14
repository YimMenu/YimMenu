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
	    {eSessionType::CLOSED_CREW, "Closed Crew Session"},
	    {eSessionType::CREW, "Crew Session"},
	    {eSessionType::CLOSED_FRIENDS, "Closed Friend Session"},
	    {eSessionType::FIND_FRIEND, "Find Friend Session"},
	    {eSessionType::SOLO, "Solo Session"},
	    {eSessionType::INVITE_ONLY, "Invite Only Session"},
	    {eSessionType::JOIN_CREW, "Join Crew Session"},
	    {eSessionType::SC_TV, "SC TV"},
	    {eSessionType::LEAVE_ONLINE, "Leave GTA Online"},
	};
}