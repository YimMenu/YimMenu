#include "hooking/hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"

namespace big
{
	void hooks::send_session_detail_msg(rage::netConnectionManager* mgr, rage::netConnection::InFrame* request_frame, rage::rlSessionDetailMsg* msg)
	{
		if (g_matchmaking_service) [[likely]]
			g_matchmaking_service->handle_session_detail_send_response(msg);

		g_hooking->get_original<hooks::send_session_detail_msg>()(mgr, request_frame, msg);
	}
}