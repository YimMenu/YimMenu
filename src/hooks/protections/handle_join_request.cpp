#include "hooking.hpp"
#include "pointers.hpp"
#include "services/bad_players/bad_players.hpp"
#include "services/notifications/notification_service.hpp"

#include <network/CJoinRequestContext.hpp>
#include <network/CMsgJoinResponse.hpp>
#include <network/snSession.hpp>

namespace big
{
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session)
	{
		auto rockstar_id = player_info->m_gamer_handle.m_rockstar_id;

		if (bad_players_nm::is_blocked(rockstar_id))
		{
			CMsgJoinResponse response{};
			response.m_status_code = 21;
			g_pointers->m_gta.m_write_join_response_data(&response, ctx->m_join_response_data, 512, &ctx->m_join_response_size);

			auto is_spammer = bad_players_nm::bad_players_list[rockstar_id].is_spammer;

			auto str = std::format("Join Request denied to {} {} ({})", is_spammer ? "Spammer" : "Player", player_info->m_name, rockstar_id);

			if (is_spammer)
				LOG(WARNING) << str;
			else
				g_notification_service->push_success("Join Blocked", str, true);

			return false;
		}
		else
			return g_hooking->get_original<hooks::handle_join_request>()(network, session, player_info, ctx, is_transition_session);
	}
}