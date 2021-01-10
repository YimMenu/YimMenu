#include "features/notify.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "rid_joiner.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void rid_joiner::look_for_session()
	{
		if (this->awaiting_request)
		{
			features::notify::above_map("WAITING FOR GAME COORDINATOR");

			if (this->type == 2 && !this->gs_info.empty())
			{
				handle_info();
			}
		}
	}

	void rid_joiner::handle_info()
	{
		this->awaiting_request = false;

        join_rstar_id_request request;
        memset(&request, 0, sizeof(request));
		request.identifier.rockstar_id = g_pointers->m_rs_info->rockstar_id;
		request.identifier.type = 3;

		features::notify::above_map("ATTEMPTING TO JOIN");

		g_pointers->m_get_session_info_from_gs(&request.session_info, this->gs_info.c_str(), 0, 0);
		g_pointers->m_join_player_via_session_info(&request.identifier, &request.session_info, 0xA000);
    }

	void rid_joiner::join_player(uint64_t rid)
	{
		this->awaiting_request = true;
		this->gs_info.clear();
		this->type = 2;
        this->rid = rid;

		rockstar_identifier* identifier = new rockstar_identifier();
		identifier->rockstar_id = rid;
		identifier->type = 3;
		NETWORK::NETWORK_CLEAR_GET_GAMER_STATUS();

		g_pointers->m_send_session_info_request(identifier, 1);

		features::notify::above_map("Sent join request to join R* Id.");
	}
}