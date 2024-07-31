#include "hooking/hooking.hpp"
#include "pointers.hpp"
#include "services/friends/friends_service.hpp"
#include "services/player_database/player_database_service.hpp"

#include <network/CJoinRequestContext.hpp>
#include <network/CMsgJoinResponse.hpp>
#include <network/snSession.hpp>

namespace big
{
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session)
	{
		auto rockstar_id = player_info->m_gamer_handle.m_rockstar_id;
		auto is_friend   = friends_service::is_friend(rockstar_id);
		auto db_player   = g_player_database_service->get_player_by_rockstar_id(rockstar_id);
		auto block_join  = db_player && db_player->block_join;
		auto is_trusted  = db_player && db_player->is_trusted;
		auto player_name = player_info->m_name;

		auto send_response = [ctx](int block_join_reason = 1) {
			CMsgJoinResponse response{};
			response.m_status_code = block_join_reason;
			g_pointers->m_gta.m_write_join_response_data(&response, ctx->m_join_response_data, 512, &ctx->m_join_response_size);
		};

		if (block_join)
		{
			send_response(db_player->block_join_reason);
			g_notification_service.push("BLOCK_JOIN"_T.data(), std::vformat("BLOCK_JOIN_INFO"_T, std::make_format_args(player_name)));
			return false;
		}
		else if (g.session.lock_session)
		{
			if ((is_friend && g.session.allow_friends_into_locked_session) || is_trusted)
			{
				g_notification_service.push_success("LOBBY_LOCK"_T.data(), std::vformat("LOBBY_LOCK_ALLOWED"_T.data(), std::make_format_args(player_name)));
			}
			else
			{
				send_response();
				g_notification_service.push_warning("LOBBY_LOCK"_T.data(), std::vformat("LOBBY_LOCK_DENIED"_T.data(), std::make_format_args(player_name)));
				return false;
			}
		}

		return g_hooking->get_original<hooks::handle_join_request>()(network, session, player_info, ctx, is_transition_session);
	}
}
