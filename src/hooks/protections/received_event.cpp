#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include <network/CNetGamePlayer.hpp>
#include "gta/script_id.hpp"

namespace big
{
	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	void hooks::received_event(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		int buffer_size,
		rage::datBitBuffer* buffer
	)
	{
		if (event_id > 91u)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

			return;
		}

		const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		switch (static_cast<eNetworkEvents>(event_id))
		{
		case eNetworkEvents::KICK_VOTES_EVENT:
		{
			std::uint32_t player_bitfield = buffer->Read<uint32_t>(32);
			if (player_bitfield & (1 << target_player->m_player_id))
			{
				if (g->notifications.received_event.kick_vote.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " is voting to kick us.";
				if (g->notifications.received_event.kick_vote.notify)
					g_notification_service->push_warning("Kick Vote", std::format("{} is voting to kick us.", source_player->get_name()));
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::NETWORK_INCREMENT_STAT_EVENT:
		{
			const auto increment_stat_event = std::make_unique<CNetworkIncrementStatEvent>();
			buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
			buffer->ReadDword(&increment_stat_event->m_amount, 0x20);
			if (hooks::increment_stat_event(increment_stat_event.get(), source_player))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPT_ENTITY_STATE_CHANGE_EVENT:
		{
			uint16_t entity = buffer->Read<uint16_t>(13);
			auto type = buffer->Read<ScriptEntityChangeType>(4);
			uint32_t unk = buffer->Read<uint32_t>(32);
			if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction) 
			{
				uint16_t unk2 = buffer->Read<uint16_t>(13);
				uint32_t action = buffer->Read<uint32_t>(8);

				if (action >= 15 && action <= 18 || action == 33) 
				{
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

					if (g->notifications.received_event.vehicle_temp_action.log)
						LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent TASK_VEHICLE_TEMP_ACTION crash.";
					if (g->notifications.received_event.vehicle_temp_action.notify)
						g_notification_service->push_error("Protections", std::format("{} sent TASK_VEHICLE_TEMP_ACTION crash.", source_player->get_name()));

					return;
				}
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPTED_GAME_EVENT:
		{
			const auto scripted_game_event = std::make_unique<CScriptedGameEvent>();
			buffer->ReadDword(&scripted_game_event->m_args_size, 32);
			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			if (hooks::scripted_game_event(scripted_game_event.get(), source_player))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			buffer->Seek(0);

			break;
		}
		case eNetworkEvents::NETWORK_CLEAR_PED_TASKS_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				if (g->notifications.received_event.clear_ped_task.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent CLEAR_PED_TASKS event.";
				if (g->notifications.received_event.clear_ped_task.notify)
					g_notification_service->push_warning("Protections", std::format("{} tried to freeze player.", source_player->get_name()));

				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::RAGDOLL_REQUEST_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				if (g->notifications.received_event.clear_ped_task.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent RAGDOLL_REQUEST event.";
				if (g->notifications.received_event.clear_ped_task.notify)
					g_notification_service->push_warning("Protections", std::format("{} tried to ragdoll player.", source_player->get_name()));

				return;
			}

			buffer->Seek(0);
			break;
		}
		// Don't block this event, we still want to report this player
		// because if we still report others, our account seems less fishy
		case eNetworkEvents::REPORT_CASH_SPAWN_EVENT:
		{
			uint32_t money;

			buffer->Seek(64);
			buffer->ReadDword(&money, 32);
			buffer->Seek(0);

			if (money >= 2000)
			{
				if (g->notifications.received_event.report_cash_spawn.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent REPORT_CASH_SPAWN event.";
				if (g->notifications.received_event.report_cash_spawn.notify)
					g_notification_service->push_warning("Protections", std::format("{} is spawning cash.", source_player->get_name()));
			}

			break;
		}
		// player sending this event is a modder
		case eNetworkEvents::NETWORK_CHECK_CODE_CRCS_EVENT:
		case eNetworkEvents::REPORT_MYSELF_EVENT:
		{
			if (g->notifications.received_event.modder_detect.log)
				LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent modder event.";
			if (g->notifications.received_event.modder_detect.notify)
				g_notification_service->push_warning("Protections", std::format("{} sent out a modder event.", source_player->get_name()));

			break;
		}
		case eNetworkEvents::REQUEST_CONTROL_EVENT:
		{
			int net_id = buffer->Read<int>(13);
			if (g_local_player && g_local_player->m_vehicle && g_local_player->m_vehicle->m_net_object && g_local_player->m_vehicle->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				if (g->notifications.received_event.request_control_event.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " requested control of player vehicle.";
				if (g->notifications.received_event.request_control_event.notify)
					g_notification_service->push_warning("Protections", std::format("Denied player control request from {}", source_player->get_name()));

				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPT_WORLD_STATE_EVENT:
		{
			auto type = buffer->Read<WorldStateDataType>(4);
			(void)buffer->Read<bool>(1);
			CGameScriptId id;
			script_id_deserialize(id, *buffer);

			if (type == WorldStateDataType::Rope)
			{
				buffer->Read<int>(9); // unk
				buffer->Read<float>(19); // pos x
				buffer->Read<float>(19); // pos y
				buffer->Read<float>(19); // pos z
				buffer->Read<float>(19); // rot x
				buffer->Read<float>(19); // rot y
				buffer->Read<float>(19); // rot z
				buffer->Read<float>(16); // length
				int type = buffer->Read<int>(4);

				if (type != 7)
				{
					// most definitely a crash
					g_notification_service->push_error("Protections", std::format("{} sent rope crash.", source_player->get_name()));
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type == WorldStateDataType::PopGroupOverride)
			{
				int unk = buffer->ReadSigned<int>(8);
				int unk2 = buffer->Read<int>(32);
				int unk3 = buffer->Read<int>(7);

				if (unk2 == 0 && (unk3 == 0 || unk3 == 103))
				{
					g_notification_service->push_error("Protections", std::format("{} sent SCRIPT_WORLD_STATE_EVENT crash.", source_player->get_name()));
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::REMOVE_WEAPON_EVENT:
		{
			int net_id = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);

			if (hash == RAGE_JOAAT("WEAPON_UNARMED"))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_notification_service->push_warning("Protections", std::format("{} tried to remove a weapon.", source_player->get_name()));
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::REMOVE_ALL_WEAPONS_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_notification_service->push_warning("Protections", std::format("{} tried to remove all weapons.", source_player->get_name()));
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		default:
			break;
		}

		return g_hooking->get_original<received_event>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
	}
}
