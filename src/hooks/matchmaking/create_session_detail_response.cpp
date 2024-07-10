#include "hooking/hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"
#include <network/snSession.hpp>

namespace big
{
	void hooks::send_session_detail_msg(rage::netConnectionManager* mgr, rage::netConnection::InFrame* request_frame, rage::rlSessionDetailMsg* msg)
	{
		if (g_matchmaking_service) [[likely]]
			g_matchmaking_service->handle_session_detail_send_response(msg);

		if (g.session.hide_token_spoofing_when_host)
			msg->m_detail.m_host_token = g.session.original_host_token;

		g_hooking->get_original<hooks::send_session_detail_msg>()(mgr, request_frame, msg);
	}
}