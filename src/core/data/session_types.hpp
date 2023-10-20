#pragma once
#include "core/enums.hpp"

namespace big
{
	struct SessionType
	{
		eSessionType id;
		std::string_view name;
	};

	const SessionType sessions[] = {
	    {eSessionType::JOIN_PUBLIC, "BACKEND_SESSION_TYPE_JOIN_PUBLIC"_T},
	    {eSessionType::NEW_PUBLIC, "BACKEND_SESSION_TYPE_NEW_PUBLIC"_T},
	    {eSessionType::CLOSED_CREW, "BACKEND_SESSION_TYPE_CLOSED_CREW"_T},
	    {eSessionType::CREW, "BACKEND_SESSION_TYPE_CREW"_T},
	    {eSessionType::CLOSED_FRIENDS, "BACKEND_SESSION_TYPE_CLOSED_FRIENDS"_T},
	    {eSessionType::FIND_FRIEND, "BACKEND_SESSION_TYPE_FIND_FRIEND"_T},
	    {eSessionType::SOLO, "BACKEND_SESSION_TYPE_SOLO"_T},
	    {eSessionType::INVITE_ONLY, "BACKEND_SESSION_TYPE_INVITE_ONLY"_T},
	    {eSessionType::JOIN_CREW, "BACKEND_SESSION_TYPE_JOIN_CREW"_T},
	    {eSessionType::SC_TV, "BACKEND_SESSION_TYPE_SC_TV"_T},
	    {eSessionType::LEAVE_ONLINE, "BACKEND_SESSION_TYPE_LEAVE_ONLINE"_T},
	};
}