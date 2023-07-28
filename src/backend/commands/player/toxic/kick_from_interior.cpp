#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/script_handler.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/script_connection/script_connection_service.hpp"
#include "util/scripts.hpp"

#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class kick_from_interior : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			if (scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[player->id()].PropertyData.Index != -1)
			{
				auto cxn = g_script_connection_service->create_connection("am_mp_property_int", player);
				cxn->set_host_broadcast_size(1359);
				cxn->set_player_broadcast_size(1185);
				cxn->set_no_remote_start(true);
				cxn->set_wait_for_host_broadcast_data(true);
				cxn->set_quick_cleanup(true);
				cxn->set_debug_logging(true);
				cxn->set_broadcast_modify_callback([](rage::scrThread* thread, uint64_t* server_vars, uint64_t* client_vars) {
					server_vars[718] = 1;
				});

				g_fiber_pool->queue_job([cxn] {
					cxn->start();
				});
			}
			else
			{
				const size_t arg_count = 8;
				int64_t args[arg_count]{
				    (int64_t)eRemoteEvent::KickFromInterior,
				    (int64_t)self::id,
				    (int64_t)scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()
				        ->Entries[player->id()]
				        .SimpleInteriorData.Index,
				    (int64_t)scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()
				        ->Entries[player->id()]
				        .SimpleInteriorData.InstanceId,
				};

				g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
			}
		}
	};

	kick_from_interior g_kick_from_interior("intkick", "KICK_FROM_INTERIOR", "KICK_FROM_INTERIOR_DESC", 0);
}