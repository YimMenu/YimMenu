#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/script_handler.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

#include <script/globals/GPBD_FM.hpp>

namespace big
{
	class kick_from_interior : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[player->id()].PropertyData.Index != -1)
			{
				int id = player->id();
				g_fiber_pool->queue_job([id] {
					int instance = -1;

					for (int i = 0; i < 32; i++)
					{
						if (NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_mp_property_int", i))
						{
							instance = i;
							break;
						}
					}


					if (instance == -1)
					{
						return;
					}

					while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(RAGE_JOAAT("am_mp_property_int")))
					{
						SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("am_mp_property_int"));
						script::get_current()->yield();
					}

					auto program = gta_util::find_script_program(RAGE_JOAAT("am_mp_property_int"));

					int count              = program->m_local_count;
					program->m_local_count = 2;
					int id = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("am_mp_property_int"), 1424);
					program->m_local_count = count;

					auto script = gta_util::find_script_thread_by_id(id);

					if (!script)
						return;

					script->m_context.m_state = rage::eThreadState::unk_3;


					gta_util::execute_as_script(script, [instance] {
						if (auto hook =
						        g_hooking->m_handler_hooks[(CGameScriptHandler*)rage::scrThread::get()->m_handler].get())
						{
							hook->disable();
							g_hooking->m_handler_hooks.erase((CGameScriptHandler*)rage::scrThread::get()->m_handler);
						}

						NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(32, true, instance);
					});

					for (int i = 0; i < 100; i++)
					{
						int status = 0;
						gta_util::execute_as_script(script, [&status] {
							status = NETWORK::NETWORK_GET_SCRIPT_STATUS();
						});

						if (status == 2)
							break;

						if (status > 2)
						{
							script->kill();
							return;
						}

						script::get_current()->yield(50ms);
					}

					static uint64_t server_vars[1358]{};
					static uint64_t client_vars[1185]{};

					gta_util::execute_as_script(script, [] {
						NETWORK::NETWORK_REGISTER_HOST_BROADCAST_VARIABLES((int*)server_vars, 1358, 0);
						NETWORK::NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((int*)client_vars, 1185, 0);
					});

					for (int i = 0; i < 3600; i++)
					{
						bool received = false;
						gta_util::execute_as_script(script, [&received] {
							received = NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA();
						});

						if (received)
							break;

						script::get_current()->yield();
					}

					if (!scripts::force_host(RAGE_JOAAT("am_mp_property_int")))
					{
						script->kill();
						return;
					}

					server_vars[717] = 1;
					script::get_current()->yield(3s);

					script->kill();
				});
			}
			else
			{
				const size_t arg_count = 8;
				int64_t args[arg_count]{
				    (int64_t)eRemoteEvent::KickFromInterior,
				    (int64_t)self::id,
				    *scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(321).at(7).as<int64_t*>(),
				    *scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(321).at(8).as<int64_t*>(),
				};

				g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
			}
		}
	};

	kick_from_interior g_kick_from_interior("intkick", "Kick From Interior", "Kicks the player from the interior they are in", 0);
}