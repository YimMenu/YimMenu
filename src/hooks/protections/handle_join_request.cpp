#include "hooking.hpp"
#include "services/player_database/player_database_service.hpp"
#include "pointers.hpp"
#include <network/snSession.hpp>
#include <network/CMsgJoinResponse.hpp>
#include <network/CJoinRequestContext.hpp>

namespace big
{
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session)
	{
		if (auto player = g_player_database_service->get_player_by_rockstar_id(player_info->m_gamer_handle_2.m_rockstar_id); player && player->block_join)
		{
			CMsgJoinResponse response{};
			response.m_status_code = player->block_join_reason;
			g_pointers->m_write_join_response_data(&response, ctx->m_join_response_data, 512, &ctx->m_join_response_size);
			g_notification_service->push("Block Join", std::format("Blocked {} from joining", player->name));
			return false;
		}
		else
		{
			return g_hooking->get_original<hooks::handle_join_request>()(network, session, player_info, ctx, is_transition_session);
		}
	}
}